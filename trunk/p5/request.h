#ifndef __REQUEST_H__
#include "server.h"

void requestHandle(request_type request, thread_info_type* thread_info );
request_type requestParse(request_type request);

#endif
