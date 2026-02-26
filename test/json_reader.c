#include <stdio.h>
#include <stdlib.h>

#include <json-c/json.h>

int main(){
    FILE *fp;
    char buffer[1024];

    struct json_object *parsed_json;
    struct json_object *size_x;
    struct json_object *size_y;
    struct json_object *frame_rate;

    printf("obj défini\n");

    fp = fopen("data/configuration.json", "r");
    if(fp == NULL){
        printf("Fichier non trouvé\n");
        return EXIT_FAILURE;
    }
    else{
        printf("fichier ouvert\n");
    }
    fread(buffer, 1024, 1, fp);
    printf("fichier lu\n");

    fclose(fp);
    printf("fichier fermé\n");

    parsed_json = json_tokener_parse(buffer);
    printf("elt parser\n");

    json_object_object_get_ex(parsed_json, "size_x", &size_x);
    json_object_object_get_ex(parsed_json, "size_y", &size_y);
    json_object_object_get_ex(parsed_json, "frame_rate", &frame_rate);

    printf("attribution des elt fait\n");

    printf("%d", json_object_get_int(size_x));
    return EXIT_SUCCESS;
}