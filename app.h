#ifndef APP_H
#define APP_H

/*
    The app structure and functions pertaining to general apps
*/

typedef struct app App;
//typedef int (user_func*) (void *); //for manipulating the user data

//creation
App *createApp();

//deletion
void destroyApp(App *a);

/*
==========================================
mutation
==========================================
*/


/*
    adds data to the userData field
    if data is dynamically allocated, must be handled elsewhere
*/
void setUserData(void *data);


/*
==========================================
getters
==========================================
*/


/*
    returns the user data
*/
void *getUserData(App *);

#endif
