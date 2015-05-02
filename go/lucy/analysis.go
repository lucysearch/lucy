/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package lucy

/*
#include "Lucy/Analysis/Analyzer.h"
#include "Lucy/Analysis/EasyAnalyzer.h"
*/
import "C"
import "unsafe"

import "git-wip-us.apache.org/repos/asf/lucy-clownfish.git/runtime/go/clownfish"

type Analyzer interface {
	clownfish.Obj
}

type AnalyzerIMP struct {
	clownfish.ObjIMP
}

type EasyAnalyzer interface {
	Analyzer
}

type EasyAnalyzerIMP struct {
	AnalyzerIMP
}

func NewEasyAnalyzer(language string) EasyAnalyzer {
	lang := clownfish.NewString(language)
	cfObj := C.lucy_EasyAnalyzer_new((*C.cfish_String)(unsafe.Pointer(lang.TOPTR())))
	return WRAPEasyAnalyzer(unsafe.Pointer(cfObj))
}

func WRAPEasyAnalyzer(ptr unsafe.Pointer) EasyAnalyzer {
	obj := &EasyAnalyzerIMP{}
	obj.INITOBJ(ptr);
	return obj
}
