//
// Created by giova on 04/12/2019.
//

#ifndef SERVERMODULE_EMAIL_H
#define SERVERMODULE_EMAIL_H

#include <curl/curl.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <sstream>

static const char *payload_text[] = {
    //"Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n", //this will be substituted with the current date
    "To: \r\n", //this will be substituted with the correct email
    "From: Carte Editor\r\n",
    //"Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efk@" "rfcpedant.example.org>\r\n",//leave this line commented because the
    "Subject: Sei stato invitato a collaborare\r\n",
    "\r\n", /* empty line to divide headers from body, see RFC5322 */
    "The body of the message starts here.\r\n", //this will be substituted with the URI of the file
    "\r\n",
    "Buon lavoro!\r\n",
    "TEAM C.A.R.T.E.\r\n",
    nullptr
};

struct upload_status {
    int lines_read;
};

class email {
    public:
        static bool sendEmail(const std::string& email, const std::string& uri);
    private:
        static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
};


#endif //SERVERMODULE_EMAIL_H
