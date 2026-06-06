# Security Policy

## Reporting a Vulnerability

Use GitHub's Security Advisories feature to report security concerns
privately.

Expect a response within 7 days. If the issue is confirmed, a fix
will be released as a patch version.

## Scope

observer is a small C++ observer pattern library with no network stack
and no external dependencies. The primary attack surface is use-after-free
in observer callbacks and integer overflow in subscriber count tracking.
