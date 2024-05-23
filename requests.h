#ifndef _REQUESTS_
#define _REQUESTS_

// computes and returns a GET request string (cookies/token can be NULL if not needed)
char *compute_get_request(char *host, char *url, char *cookies, char *token);

// computes and returns a POST request string (cookies can be NULL if not needed)
char *compute_post_request(char *host, char *url, char* content_type, char *body_data,
                            char **cookies, int cookies_count);

#endif
