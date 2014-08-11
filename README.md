nginx-dummy-module
==================

# Installation
    Configure dummy module as nginx module with ```--add-module``` when build nginx
    git clone https://github.com/mbIkola/nginx-dummy-module  ~/nginx-dummy-module

    cd /path/somewhere/where/nginx/source/tree/stored
    ./configure --add-module=~/nginx-dummy-module
    make && make install


# Configuration
There are no special configuration rules for that module. 
But should be something like this:

    http { 
        dummy_module on; #turn on dummy module functions
        
        server {
            server_name something.burning.com; 

            dummy_module_server_variable "server value"; 
            ...
            location / {
                dummy_module_location_variable "location value"; 
                ...
            }
        }
    }


# Usage
This module does nothing. It's just skeleton module for nginx. 

# Branches
 * master  Main branch


# Author 
 Nickolay Kharchevin  [Github](https://github.com/mbIkola)


# Release History
_(Nothing yet)_
 

# License
 
Licensed under the WTFPL license;
 

# Thanks
Thank you to everyone at Filmon for giving me the opportunity. 
I give my most sincere thanks and appreciation  to everyone who helped this module come to fruition. 
A special thanks to Anastasia and Alex, your constant love, help and encouragement mean so much to me. 
I love sharing all my thoughts and dreams with you. 

