/* charmonize.c -- write lucyconf.h config file.
 */

#include "Charmonizer/Core.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Charmonizer.h"
#include "Charmonizer/FuncMacro.h"
#include "Charmonizer/Integers.h"
#include "Charmonizer/LargeFiles.h"
#include "Charmonizer/UnusedVars.h"
#include "Charmonizer/VariadicMacros.h"

/* Process command line args, set up Charmonizer, etc. Returns the outpath
 * (where the config file should be written to).
 */
char*
init(int argc, char **argv);

/* Find <tag_name> and </tag_name> within a string and return the text between
 * them as a newly allocated substring.
 */
static char*
extract_delim(char *source, size_t source_len, const char *tag_name);

/* Assign the location where the config file will be written.
 */
static void 
set_outpath(char* path);

/* Start the config file.
 */
static void 
start_conf_file();

/* Write the last bit of the config file.
 */
static void 
finish_conf_file(FILE *fh);

/* Print a message to stderr and exit.
 */
void
die(char *format, ...);

int main(int argc, char **argv) 
{
    FILE *config_fh;

    /* parse commmand line args, init Charmonizer, open outfile */
    char *outpath = init(argc, argv);
    config_fh = fopen(outpath, "w");
    if (config_fh == NULL)
        die("Couldn't open '%s': %s", strerror(errno));
    start_conf_file(config_fh);

    /* modules section */
    chaz_FuncMacro_run(config_fh);
    chaz_Integers_run(config_fh);
    chaz_LargeFiles_run(config_fh);
    chaz_UnusedVars_run(config_fh);
    chaz_VariadicMacros_run(config_fh);

    /* write tail of config and clean up */
    finish_conf_file(config_fh);
    if (fclose(config_fh))
        die("Error closing file '%s': %s", outpath, strerror(errno));
    free(outpath);

    return 0;
}

char* 
init(int argc, char **argv) 
{
    int i;
    char *outpath, *compiler, *ccflags;
    char *infile_contents;
    size_t infile_len;

    /* parse the infile */
    if (argc != 2)
        die("Usage: ./charmonize INFILE");
    infile_contents = chaz_slurp_file(argv[1], &infile_len);
    compiler = extract_delim(infile_contents, infile_len, "charm_compiler");
    ccflags  = extract_delim(infile_contents, infile_len, "charm_ccflags");
    outpath  = extract_delim(infile_contents, infile_len, "charm_outpath");
    
    /* set up Charmonizer */
    chaz_set_prefixes("LUCY_", "Lucy_", "lucy_", "lucy_");
    chaz_set_compiler(compiler);
    chaz_set_ccflags(ccflags);

    /* clean up */
    free(infile_contents);
    free(compiler);
    free(ccflags);

    return outpath;
}

static char*
extract_delim(char *source, size_t source_len, const char *tag_name)
{
    const size_t tag_name_len = strlen(tag_name);
    const size_t opening_delim_len = tag_name_len + 2;
    const size_t closing_delim_len = tag_name_len + 3;
    char opening_delim[100];
    char closing_delim[100];
    const char *limit = source + source_len - closing_delim_len;
    char *start, *end;
    char *retval = NULL;

    /* sanity check, then create delimiter strings to match against */
    if (tag_name_len > 95)
        die("tag name too long: '%s'");
    sprintf(opening_delim, "<%s>\0", tag_name);
    sprintf(closing_delim, "</%s>\0", tag_name);
    
    /* find opening <delimiter> */
    for (start = source; start < limit; start++) {
        if (strncmp(start, opening_delim, opening_delim_len) == 0) {
            start += opening_delim_len;
            break;
        }
    }

    /* find closing </delimiter> */
    for (end = start; end < limit; end++) {
        if (strncmp(end, closing_delim, closing_delim_len) == 0) {
            const size_t retval_len = end - start;
            retval = (char*)malloc((retval_len + 1) * sizeof(char));
            retval[retval_len] = '\0';
            strncpy(retval, start, retval_len);
            break;
        }
    }

    if (retval == NULL)
        die("Couldn't extract value for '%s'", tag_name);
    
    return retval;
}

static void 
start_conf_file(FILE *conf_fh) 
{
    fprintf(conf_fh,
        "/* Header file auto-generated by Charmonizer. \n"
        " * DO NOT EDIT THIS FILE!!\n"
        " */\n\n"
        "#ifndef H_LUCY_CONF\n"
        "#define H_LUCY_CONF 1\n\n"
    );
}

static void
finish_conf_file(FILE *conf_fh) 
{
    fprintf(conf_fh,
        "/* conf end */\n"
        "#ifdef LUCY_USE_SHORT_NAMES\n"
        "# define bool_t                    lucy_bool_t\n"
        "# define i8_t                      lucy_i8_t\n"
        "# define u8_t                      lucy_u8_t\n"
        "# define i16_t                     lucy_i16_t\n"
        "# define u16_t                     lucy_u16_t\n"
        "# define i32_t                     lucy_i32_t\n"
        "# define u32_t                     lucy_u32_t\n"
        "# define i64_t                     lucy_i64_t\n"
        "# define u64_t                     lucy_u64_t\n"
        "# define Unused_Var(x)             Lucy_Unused_Var(x)\n"
        "# define Unreachable_Return(type)  Lucy_Unreachable_Return(type)\n"
        "# define FSeek                     lucy_FSeek\n"
        "# define FTell                     lucy_FTell\n"
        "#endif\n"
    );

    fprintf(conf_fh, 
        "\n\n#endif /* H_LUCY_CONF */\n\n"
    );
}

void 
die(char* format, ...) 
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(1);
}

/**
 * Copyright 2006 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

