    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <curl/curl.h>
    #include <json-c/json.h>


    typedef struct {
        char name[100];
        long population;
    }Country;

    struct string {
        char *ptr;
        size_t len;
    };

    void init_string(struct string *s) {
        s->len = 0;
        s->ptr = malloc(s->len + 1);
        if (s->ptr == NULL) {
            fprintf(stderr, "malloc() failed\n");
            exit(EXIT_FAILURE);
        }
        s->ptr[0] = '\0';
    }

    size_t write_func(void *ptr, size_t size, size_t nmemb, struct string *s) {
        size_t new_len = s->len + size*nmemb;
        s->ptr = realloc(s->ptr, new_len + 1);
        if (s->ptr == NULL) {
            fprintf(stderr, "realloc() failed\n");
            exit(EXIT_FAILURE);
        }

        memcpy(s->ptr + s->len, ptr, size*nmemb);
        s->ptr[new_len] =  '\0';
        s->len = new_len;

        return size*nmemb;
    }

    int compareCountries(const void *a, const void *b) {
        Country *countryA = (Country *)a;
        Country *countryB = (Country *)b;

        if (countryA->population != countryB->population) {
            return (countryA->population - countryB->population);
        }

        return(strcmp(countryA->name, countryB->name));
    }

    void findCountries(char *region, char *keyword) {
        CURL *curl;
        CURLcode res;
        struct string s;
        init_string(&s);

        curl = curl_easy_init();
        if(curl) {
            char url[256];
            sprintf(url, "https://jsonmock.hackerrank.com/api/countries/search?region=%s&name=%s", region, keyword);

            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

            } else {
                // Parse JSON
                struct json_object *parsed_json;
                struct json_object *data_array;
                parsed_json = json_tokener_parse(s.ptr);

                json_object_object_get_ex(parsed_json, "data", &data_array);
                int data_length = json_object_array_length(data_array);

                Country countries[100];
                int country_count = 0;

                //Process each country
                for (int i = 0; i < data_length; i++) {

                    struct json_object *country_obj =
                        json_object_array_get_idx(data_array, i);

                    struct json_object *name;
                    struct json_object *population;

                    json_object_object_get_ex(country_obj, "name", &name);
                    json_object_object_get_ex(country_obj, "population", &population);

                    strcpy(countries[country_count].name, json_object_get_string(name));
                    countries[country_count].population = json_object_get_int64(population);
                    country_count++;
                }

                //Order countries
                qsort(countries, country_count, sizeof(Country), compareCountries);

                for (int i = 0; i < country_count; i++) {
                    printf("%s, %ld\n", countries[i].name, countries[i].population);
                }
            }

            curl_easy_cleanup(curl);
            free(s.ptr);

        }
    }

    int main(void)
    {

        findCountries("Europe", "por" );

        return 0;
    }
