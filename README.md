# Allow setuid on shell scripts - setuid_wrapper

Running shell script in setuid is disabled by default from most Linux distrubutions due to security reasons. If you still have the need to "setuid", you could recompile the kenrel, or by calling the shell script from a C wrapper as mentioned here: https://access.redhat.com/solutions/124693

The C code here is an enhanced version with following features added:
* Passing arguments when calling the shell script
* Calling argv[0].sh, means you can rename it to any other name, such as "foo", then calling foo will be redirected to foo.sh with all the arguments

So, compile and install it:
* gcc wrapper.c -o foo
* cp foo /bin/
* chmod 4711 /bin/foo
* chmod 700 /bin/foo.sh
