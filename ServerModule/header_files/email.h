//
// Created by giova on 04/12/2019.
//

#ifndef SERVERMODULE_EMAIL_H
#define SERVERMODULE_EMAIL_H

#include <curl/curl.h>
#include <iostream>
#include <cstring>

static const char *payload_text[] = {
        /*"Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
        "To: " TO_MAIL "\r\n",*/
        "From: Carte Editor\r\n",

        //"Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efk@" "rfcpedant.example.org>\r\n",//leave this line commented because the
        "Subject: You have been invited to collaborate\r\n",
        "\r\n", /* empty line to divide headers from body, see RFC5322 */
        "The body of the message starts here.\r\n",
        "\r\n",
        "This function works!\r\n",
        "Check RFC5322.\r\n",
        nullptr
};

struct upload_status {
    int lines_read;
};

class email {
    public:
        static bool sendEmail();
    private:
        static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
};


#endif //SERVERMODULE_EMAIL_H
