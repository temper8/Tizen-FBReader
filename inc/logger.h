/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#define LOG_TAG "FBReader"
#include <dlog.h>

#define DLOG(prio, fmt, arg...) dlog_print(prio, LOG_TAG, "%s(%d) > " fmt, __func__, __LINE__, ##arg)
#define DBG(fmt, arg...) DLOG(DLOG_DEBUG, fmt, ##arg)
#define ERR(fmt, arg...) DLOG(DLOG_ERROR, fmt, ##arg)

#define RETM_IF(expr, fmt, arg...) \
{ \
    if (expr) \
    { \
        ERR(fmt, ##arg); \
        return; \
    } \
}

#define RETVM_IF(expr, val, fmt, arg...) \
{ \
    if (expr) \
    { \
        ERR(fmt, ##arg); \
        return (val); \
    } \
}

#endif /* __LOGGER_H__ */
