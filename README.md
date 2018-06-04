# Allow setuid on shell scripts - setuid_wrapper

Running shell script in setuid is disabled by default from most Linux distrubutions due to security reasons. If you still have the need to "setuid", you could recompile the kenrel, or by calling the shell script from a C wrapper as mentioned here: https://access.redhat.com/solutions/124693

The C code here is an enhanced version:
* Passing arguments when calling the shell script

chmod 4711 wrapper
