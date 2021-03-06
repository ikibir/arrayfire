/*******************************************************
 * Copyright (c) 2019, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#pragma once

#include <af/defines.h>

#if AF_API_VERSION >= 37

typedef void* af_event;

#ifdef __cplusplus
namespace af {

/**
    C++ RAII interface for manipulating events
*/
class AFAPI event {
    af_event e_;

   public:
    event(af_event e);
#if AF_COMPILER_CXX_RVALUE_REFERENCES
    event(event&& other);
    event& operator=(event&& other);
#endif
    event();
    ~event();

    af_event get() const;

    void mark();

    void enqueue();

    void block() const;

   private:
    event& operator=(const event& other);
    event(const event& other);
};

}  // namespace af
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
   \brief Create a new \ref af_event handle

   \param[in] eventHandle the input event handle

   \ingroup event_api
*/
AFAPI af_err af_create_event(af_event* eventHandle);

/**
   \brief Release the \ref af_event handle

   \param[in] eventHandle the input event handle

   \ingroup event_api
*/
AFAPI af_err af_delete_event(af_event eventHandle);

/**
   marks the \ref af_event on the active computation stream. If the \ref
   af_event is enqueued/waited on later, any operations that are currently
   enqueued on the event stream will be completed before any events that are
   enqueued after the call to enqueue

   \param[in] eventHandle the input event handle

   \ingroup event_api
*/
AFAPI af_err af_mark_event(const af_event eventHandle);

/**
   enqueues the \ref af_event and all enqueued events on the active stream.
   All operations enqueued after a call to enqueue will not be executed
   until operations on the stream when mark was called are complete

   \param[in] eventHandle the input event handle

   \ingroup event_api
*/
AFAPI af_err af_enqueue_wait_event(const af_event eventHandle);

/**
   blocks the calling thread on events until all events on the computation
   stream before mark was called are complete

   \param[in] eventHandle the input event handle

   \ingroup event_api
*/
AFAPI af_err af_block_event(const af_event eventHandle);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // AF_API_VERSION >= 37
