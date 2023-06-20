#include <stdio.h> 
#include <curl/curl.h> 
 
int downloadFile(const char *url, const char *filepath) 
{ 
    CURL *curl; 
    FILE *fp; 
    CURLcode res; 
 
    // Initialize the curl handle
    curl = curl_easy_init(); 
    if (!curl) {
        fprintf(stderr, "Error: Failed to initialize curl\n");
        return 1;
    }

    // Open the output file in binary mode for writing
    fp = fopen(filepath, "wb"); 
    if (!fp) { 
        fprintf(stderr, "Error: Failed to open file '%s'\n", filepath); 
        curl_easy_cleanup(curl);
        return 1; 
    } 

    // Set the URL to download
    curl_easy_setopt(curl, CURLOPT_URL, url); 

    // Set the write function to receive data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite); 

    // Set the write data to be written to the file pointer "fp"
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); 

    // Execute the download and save the result in "res" variable
    res = curl_easy_perform(curl); 

    // Check for errors
    if (res != CURLE_OK) { 
        fprintf(stderr, "Error: Failed to download file %s\n", curl_easy_strerror(res)); 
        curl_easy_cleanup(curl);
        fclose(fp);
        return 1; 
    } 

    // Clean up and free resources
    curl_easy_cleanup(curl); 

    // Close the file
    fclose(fp); 

    return 0; 
}

int main(void) 
{ 
    const char *url = "https://example.com";
    const char *filepath = "downloaded-html/example.html"; 

    int result = downloadFile(url, filepath);
    if (result != 0) {
        fprintf(stderr, "Error: Failed to download file\n");
        return 1;
    }

    printf("File downloaded successfully.\n");
    return 0; 
} 

