/* File : isoObject.i */
%module isoObject_wrap
#ifdef SWIGJAVA
%javaconst(0);
#endif
%pointer_functions(uint32_t, uint32ptr);
%include <std_string.i>
%include <std_vector.i>
%include <stdint.i>
%include <cpointer.i>
%include <typemaps.i>
%rename(LessThan) operator<(const Transition &lhs, const Transition &rhs);

%rename(basicSockEqualsRef) operator=(const BasicSocket& other);
%rename(basicSockEqualsRefRef) operator=(BasicSocket&& other);
%rename(sockEqualsRef) operator=(const Socket& other);
%rename(sockEqualsRefRef) operator=(Socket&& other);

%rename(basicSockRefRef) BasicSocket(BasicSocket&& );
%rename(socketRefRef) Socket(Socket&&);

%{
#include "trajDecoder.hpp"
#include "iso22133state.hpp"
#include "iso22133object.hpp"
#include "socket.hpp"
#include "server.hpp"
#include "iso22133.h"
%}

%include "trajDecoder.hpp"
%include "iso22133state.hpp"
%include "iso22133object.hpp"
%include "socket.hpp"
%include "server.hpp"
%include "iso22133.h"


typedef double double_t;
typedef long int ssize_t;

struct timeval {
long int tv_sec;
long int tv_usec;
};



