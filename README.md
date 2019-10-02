## Server
Server is implemented with Wt C++ library.

[https://www.webtoolkit.eu/wt](https://www.webtoolkit.eu/wt)

This choose can be overkill for such project but this library contain also ORM library for DataBase, Serialisation and Authentication module.

DB implementation however, can be simply changed by implementing Database interface class. Additionaly browser based application can be very easily added if needed.

### Dependencies:
 - libwt 
 - libwthttp 
 - libwtdbo 
 - libwtsqlite3 
 - libcrypt

Wt dependency part can be downloaded from project webpage for most major systems or found in repository of most Linux systems.

### To build
Simply use CMake.

### To run it:
    ./server --docroot . --http-address 0.0.0.0 --http-port 8080

or with https

    ./server --docroot . --http-address 0.0.0.0 --http-port 8080 --https-address 0.0.0.0 --https-port 8081 (it also needs ssl keys)

or as systemd service

    cp server.service /etc/systemd/system
    systemctl daemon-reload
    systemctl start server.service

#### Sitenotes
For debug purposes it is recomended to use http session which can be monitor by for e.g. WireShark. For production it should be based on https.
User is able to view ALL events (not only created by given user).
This wasn't clarified so assumption was made. It can however, be veary easily changed in DboSession class with one line of code.
User can be registered without any protection. In production environment it should be guarded by for e.g. email verification or OAuth. It is supported by Wt and can be very easily included.

## Client
UI client is based on QtQuick.

### Dependencies:
- libjsoncpp
- libcurl

### To build
Simply use CMake.

### To run it:
    ./client

UI is simple so it is used only to demonstrade working solution. No work was made to adjust it.
Username and Password is necessary for each command. There is no feedback implemented in case of missing fields or INV response from server.
Timestamp can be set by the user, however it probably should be replaced by normal timestamp based on action time. It wasn't clarified in specification so in real situation it should be clarified.
For production environment password should be stored in encrypted form, or authorisation should be based on keys and certificates. Server part is supporting such solutions.
It can be extended also to use POST instead of GET request.
