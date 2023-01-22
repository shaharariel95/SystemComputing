#include "httpd.h"
int main(int c, char** v)
{
    serve_forever("12913");
    return 0;
}

void route(int clientfd)
{
    ROUTE_START()

    ROUTE_GET("/")
    {
        FILE* file = fopen("login.html", "r");
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);
        char* buffer = (char*) malloc(file_size * sizeof(char));
        fread(buffer, sizeof(char), file_size, file);
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("%s", buffer);
        fclose(file);
        // printf("Hello! You are using %s", request_header("User-Agent"));
        // printf(buffer);
        // write(clientfd, buffer, file_size);
    }

    ROUTE_GET("/sleeping-lions.jpg")
    {
        FILE* img = fopen("lionsleeping.png", "rb");
        fseek(img, 0, SEEK_END);
        long file_size = ftell(img);
        rewind(img);
        char* buffer = (char*) malloc(file_size * sizeof(char));
        fread(buffer, sizeof(char), file_size, img);
        printf("HTTP/1.1 200 OK\r\n");
        printf('Content-Length: %ld\r\n', file_size);
        printf('Content-Type: image/png\r\n\r\n');
        printf('Access-Control-Allow-Origin: *\r\n\r\n');

        // printf("%d", buffer);
        // size_t bytes_read;
        // while ((bytes_read = fread(buffer, 1, sizeof(buffer), img)) > 0) {
        // fwrite(buffer, 1, bytes_read, clientfd);}
        fwrite(buffer, 1 ,file_size,clientfd);
        fclose(img);
    }

    // ROUTE_GET("/pass")
    // {
    //     printf("HTTP/1.1 200 OK\r\n\r\n");
    //     printf("Hello! you got here %s , %s %s",method,uri,qs);
    // }

    ROUTE_POST("/login")
    {
        // printf("HTTP/1.1 200 OK\r\n\r\n");
        char username[150];
        char password[150];
        char action[50];
        char* token;
        const char login[50] = "Login\0";
        token = strtok(payload, "&");
        while (token != NULL) {
            if (strncmp(token, "username=", 9) == 0) {
                strcpy(username, token + 9);
            } else if (strncmp(token, "password=", 9) == 0) {
                strcpy(password, token + 9);
            } else if (strncmp(token, "action=", 7) == 0) {
                strcpy(action, token + 7);
            }
            token = strtok(NULL, "&");
        } 
        switch (strcmp(action,login)==0)
        {
        case 0: ;
            /* check if user exists and enter it into the file*/
            
            FILE *f = fopen("users.txt","a");
            fprintf(f,"%s,%s\n",username,password);
            fclose(f);
            printf("Register");
            break;
        case 1: ;
            /* check if the user exists and verify pass and redirect to homepage.*/
            // printf("");
            char line[100];
            char *saved_username = NULL;
            char *saved_pass = NULL;
            int flag = 0;
            FILE *users = fopen("users.txt", "r");
            while (fgets(line, 300, users) != NULL) {
                token = strtok(line, ",");
                saved_username = token;
                token = strtok(NULL, "\n");
                saved_pass = token;
                if (strcmp(saved_username, username) == 0) {
                    if(strcmp(saved_pass,password)==0){
                        /*User succsesfuly logged in*/
                        flag++;
                        printf("HTTP/1.1 302 Found\r\n");
                        printf("Location: /homepage?username=%s",saved_username);
                        break;
                    }else{
                        flag++;
                        FILE* file = fopen("login-wrong-pass.html", "r");
                        fseek(file, 0, SEEK_END);
                        long file_size = ftell(file);
                        rewind(file);
                        char* buffer = (char*) malloc(file_size * sizeof(char));
                        fread(buffer, sizeof(char), file_size, file);
                        printf("HTTP/1.1 200 OK\r\n\r\n");
                        printf("%s", buffer);
                        fclose(file);
                        break;
                    }
                }
            }
            if(flag == 0){
                FILE* wrong_login = fopen("login-user-was-not-found.html", "r");
                fseek(wrong_login, 0, SEEK_END);
                long file_size = ftell(wrong_login);
                rewind(wrong_login);
                char* buffer = (char*) malloc(file_size * sizeof(char));
                fread(buffer, sizeof(char), file_size, wrong_login);
                printf("HTTP/1.1 200 OK\r\n\r\n");
                printf("%s", buffer);
                fclose(wrong_login);
            }
            fclose(users);
            break;
        default:
        printf("error while getting info");
            break;
        }
    }
  
    ROUTE_GET("/homepage")
    {
        // FILE* file = fopen("homepage.html", "r");
        // fseek(file, 0, SEEK_END);
        // long file_size = ftell(file);
        // rewind(file);
        // char* buffer = (char*) malloc(file_size * sizeof(char));
        // fread(buffer, sizeof(char), file_size, file);
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("<!DOCTYPE html>\n");
        printf("<html lang='en'>\n");
        printf("<head>\n");
        printf("    <meta charset='UTF-8'>\n");
        printf("    <meta http-equiv='X-UA-Compatible' content='IE=edge'>\n");
        printf("    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n");
        printf("    <title>Dashboard</title>\n");
        printf("</head>\n");
        printf("<body style='display: flex; justify-content: center; flex-flow: wrap; background-color:gray;'>\n");
        printf("    <a style='display: flex; justify-content: center; padding: 15px; width: 100%%;' href='/'>Go back to log in page</a>\n");
        char line[100];
        char *sentence = NULL;
        char *username = NULL;
        char *token;
        char loggedname[150];
        FILE *read = fopen("data.txt", "r");
        sscanf(qs, "username=%s\n",loggedname);
        while(fgets(line, 300, read) != NULL){
            token = strtok(line, ",");
            username = token;
            token = strtok(NULL, "\n");
            sentence = token;
            // fprintf(stderr,"\n\n\n\n\n\nusername: %s, sentance: %s\n\n\n\n\n\n",username, sentence);
            if(strcmp(username,loggedname) == 0){
                printf("<div style='display: flex; margin: 3px; padding:10px; width: 100%%; justify-content: center; border-style: solid; border-width: 1px;'>%s</div>\n",sentence);
            }
        }
        printf("    <form id='form' action='/comment' method='post'  >\n"); 
        printf("        <label for='comment'>Enter a new comment</label>\n");
        printf("        <input maxlength='125' type='text' name='comm' style='background-color: lightgrey;' >\n");
        printf("        <input type='hidden' name='username' value='%s'>\n", loggedname);
        printf("        <input type='submit'name='submit' value='enter'>\n");
        printf("   </form>\n");
        printf("</body>\n");
        printf("<script>\n");
        printf("const form = document.getElementsById('form');\n");
        printf("form.addEventListener(\"submit\", function(event) {\n");
        printf("    event.preventDefault();\n");
        printf("    const formData = new FormData(form);\n");
        printf("    fetch(\"/comment\", { method: \"POST\", body: formData });\n");
        printf("});\n");
        printf("</script>\n");
        printf("</html>");
        fclose(read);
    }
    
    ROUTE_POST("/comment")
    {
        char *username;
        char *comment;
        char* token;
        fprintf(stderr,"payload: %s",payload);
        FILE *data = fopen("data.txt","a");
        token = strtok(payload, "&");
        while (token != NULL) {
            if (strncmp(token, "comm", 4) == 0) {
                comment = strchr(token, '=');
                comment++;
            }
            else if (strncmp(token, "username", 8) == 0) {
                username = strchr(token, '=');
                username++;
            }
            
            token = strtok(NULL, "&");
        }
        fprintf(stderr,"\n\n\n\n\nusername: %s,comment: %s\n\n\n\n\n",username,comment);
        fprintf(data,"%s,%s\n",username,comment);
        fclose(data);
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /homepage?username=%s",username);    }

    ROUTE_END()
}
