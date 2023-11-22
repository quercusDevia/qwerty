#include "uls.h"

//The add_file_node function creates a new t_manager structure representing a file,
//based on the existing structure oldNode. Returns a pointer to the new structure.
t_manager *add_file_node(t_manager *oldNode) {
    t_manager *newFileNode = (t_manager *)malloc(sizeof (t_manager));

    newFileNode->name = mx_strdup(oldNode->name);
    newFileNode->path = mx_strdup(oldNode->path);
    newFileNode->error = NULL;

    if (oldNode->open != NULL) {
        newFileNode->open = oldNode->open;
    }
    else if (oldNode->open == NULL){
        newFileNode->open = NULL;
    }

    if (oldNode->error != NULL) {
        newFileNode->error = mx_strdup(oldNode->error);
    }

    lstat(newFileNode->path, &(newFileNode->statistic));

    return newFileNode;
}

//The add_node function creates a new t_manager structure representing a file,
//based on the file name passed in the data parameter. Returns a pointer to the new structure.
t_manager *add_node(char *data) {
    t_manager *new_node = (t_manager *)malloc(sizeof(t_manager));

    new_node->name = mx_strdup(data);
    new_node->path = mx_strdup(data);
    new_node->error = NULL;

    if (lstat(data, &(new_node->statistic)) == -1) {
        new_node->error = mx_strdup(strerror(errno));
    }

    new_node->open = NULL;

    return new_node;
}

//The add_named_node function creates a new t_manager structure representing a named file,
//based on the name oldNamedName and path oldpath. Returns a pointer to the new structure.
t_manager *add_named_node(char *oldNamedName, char *oldpath) {
    t_manager *newNamedNode = (t_manager *) malloc(sizeof(t_manager));

    newNamedNode->name = mx_strdup(oldNamedName);

    newNamedNode->path = mx_strdup(oldpath);
    newNamedNode->path = mx_strjoin(newNamedNode->path, "/");
    newNamedNode->path = mx_strjoin(newNamedNode->path, oldNamedName);

    newNamedNode->error = NULL;

    if (lstat(newNamedNode->path, &(newNamedNode->statistic)) == -1) {
        newNamedNode->error = mx_strdup(strerror(errno));
    }

    newNamedNode->open = NULL;

    return newNamedNode;
}
