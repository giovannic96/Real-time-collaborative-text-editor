//
// Created by giova on 04/12/2019.
//

#include "header_files/email.h"

#include <utility>

bool email::sendEmail(const std::string& email, const std::string& uri) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = nullptr;
    struct upload_status upload_ctx{};

    upload_ctx.lines_read = 0;
    curl = curl_easy_init();

    if(curl) {
        //Source credentials
        curl_easy_setopt(curl, CURLOPT_USERNAME, "carte.editor@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "like->password");

        //SMTP server address and port
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

        //set Receiver
        std::string conc = "To: " + email + "\r\n";
        payload_text[0] = conc.c_str();

        //set URI to send
        std::string msgURI = "Sei stato invitato a collaborare su un documento. Inserisci questo URI per modificare il file: " + uri;
        payload_text[4] = msgURI.c_str();

        //Destination email address
        //recipients = curl_slist_append(recipients, "giorinenrfra@gmail.com");
        recipients = curl_slist_append(recipients, email.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //decomment to show log during execution

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cout << "Failed to send email." << std::endl;
            //fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return false;
        }
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
        return true;
    }
}

size_t email::payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    auto *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = payload_text[upload_ctx->lines_read];
    if(data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;
        return len;
    }
    return 0;
}
