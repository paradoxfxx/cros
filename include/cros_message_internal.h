#ifndef _CROS_MESSAGE_INTERNAL_H_
#define _CROS_MESSAGE_INTERNAL_H_

static const char* FILEEXT_MSG = "msg";

// e.g. std_msgs/String
static const char* CHAR_SEP = "/";

// character that designates a constant assignment rather than a field
static const char* CHAR_CONST = "=";

// char that denotes the comment line start
static const char* CHAR_COMMENT = "#";

static const char* HEADER_DEFAULT_PACK = "std_msgs";
static const char* HEADER_DEFAULT_NAME = "Header";
static const char* HEADER_DEFAULT_TYPE = "std_msgs/Header";

static const char* HEADER_DEFAULT_TYPEDEF =
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.secs: seconds (stamp_secs) since epoch\n"
"# * stamp.nsecs: nanoseconds since stamp_secs\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"# 0: no frame\n"
"string frame_id\n\n";

struct t_msgFieldDef
{
    CrosMessageType type;
    char* type_s;
    char* name;
    int is_array;
    int array_size;
    struct t_msgFieldDef* prev;
    struct t_msgFieldDef* next;
};

typedef struct t_msgFieldDef msgFieldDef;

struct t_msgConst
{
    CrosMessageType type;
    char* type_s;
    char* name;
    char* value;
    struct t_msgConst* prev;
    struct t_msgConst* next;
};

typedef struct t_msgConst msgConst;

struct t_msgDef
{
    char* name;
    char* package;
    char* root_dir;
    char* plain_text;
    msgFieldDef* fields;
    msgFieldDef* first_field;
    msgConst* constants;
    msgConst* first_const;
};

typedef struct t_msgDef cRosMessageDef;

struct t_msgDep
{
    cRosMessageDef* msg;
    struct t_msgDep* prev;
    struct t_msgDep* next;
};

typedef struct t_msgDep msgDep;

int getFileDependenciesMsg(char* filename, cRosMessageDef* msg, msgDep* deps);

//  Compute full text of message, including text of embedded
//  types.  The text of the main msg is listed first. Embedded
//  msg files are denoted first by an 80-character '=' separator,
//  followed by a type declaration line,'MSG: pkg/type', followed by
//  the text of the embedded type.
char* computeFullTextMsg(cRosMessageDef* msg, msgDep* deps);

int getDependenciesMsg(cRosMessageDef* msg, msgDep* msgDeps);

void cRosMD5Readable(unsigned char* data, DynString* output);

void getMD5Txt(cRosMessageDef* msg, DynString* buffer);

void initCrosMsg(cRosMessageDef* msg);

void initMsgConst(msgConst *msg);

void initCrosDep(msgDep* dep);

void initFieldDef(msgFieldDef* field);

int loadFromStringMsg(char* text, cRosMessageDef* msg);

int loadFromFileMsg(char* filename, cRosMessageDef* msg);

#endif // _CROS_MESSAGE_INTERNAL_H_