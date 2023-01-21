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

    ROUTE_GET("/sleeping-lionslirdhvlkjrdh.jpg")
    {
        FILE* img = fopen("sleeping-lion.jpg", "r");
        fseek(img, 0, SEEK_END);
        long file_size = ftell(img);
        rewind(img);
        char* buffer = (char*) malloc(file_size * sizeof(char));
        fread(buffer, sizeof(char), file_size, img);
        printf("HTTP/1.1 200 OK\r\n");
        printf('Content-Length: %ld\r\n', file_size);
        printf('Content-Type: image/jpeg\r\n\r\n');
        // printf("%d", buffer);
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), img)) > 0) {
        fwrite(buffer, 1, bytes_read, clientfd);}
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
                        printf("Location: /homepage");
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
        FILE* file = fopen("homepage.html", "r");
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);
        char* buffer = (char*) malloc(file_size * sizeof(char));
        fread(buffer, sizeof(char), file_size, file);
        printf("HTTP/1.1 200 OK\r\n\r\n");
        printf("%s", buffer);
        fclose(file);
    }
    ROUTE_END()
}
