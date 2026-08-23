# Security Policy

## Supported Versions

We actively monitor and patch security vulnerabilities. The table below outlines which versions of the project currently receive security updates:

| Version | Supported          |
| ------- | ------------------ |
| 0.7     | :white_check_mark: |
| < 0.7   | :x:                |

## Reporting a Vulnerability

**Please do not open a public GitHub issue for security vulnerabilities.** Public exposure puts all current users at risk before a fix can be issued.

Instead, please report security vulnerabilities using one of the following methods:

### Method 1: Private Vulnerability Reporting (Preferred)
You can report vulnerabilities directly and securely to project maintainers using GitHub's Private Vulnerability Reporting feature:
1. Navigate to the main page of this repository.
2. Click on the **Security** tab.
3. On the left sidebar, click **Advisories**.
4. Click **Report a vulnerability** to open the private reporting form.

### Method 2: Secure Email
If you prefer not to use GitHub's integrated tool, you can email your report to:
* **lucy@dezi.org**

Please include the following information in your report to help us evaluate it quickly:
* **Type of issue** (e.g., buffer overflow, SQL injection, XSS)
* **Location of the vulnerability** (e.g., specific file, function, or endpoint)
* **Step-by-step instructions** to reproduce the issue
* **Proof of Concept (PoC)** exploit code or payloads if available
* **Impact** of the vulnerability (what can an attacker achieve?)

We will acknowledge receipt of your vulnerability report within 48 hours.

## Our Security Process

Once a vulnerability report is received, the project maintainers will:

1. **Verify:** Investigate and confirm the vulnerability privately.
2. **Respond:** Reply with our findings and an estimated timeline for a fix.
3. **Patch:** Develop a fix in a private branch or security advisory draft.
4. **Release:** Release a new patched version and publish a GitHub Security Advisory to notify users.

## Disclosure Policy

We follow a **coordinated disclosure model**. We ask that you give us reasonable time (typically up to 90 days) to write and release a patch before you disclose the vulnerability publicly or to third parties.

## Credits

We appreciate the responsible disclosure of security vulnerabilities. With your permission, we will publicly credit you in our release notes and security advisories once the patch is published.

