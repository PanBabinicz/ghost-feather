#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

#include <stdint.h>
#include <string.h>

///
/// \breif The circular buffer instance type.
///
typedef enum
{
    CIRCULAR_BUFFER_INSTANCE_NONE = -1,
    CIRCULAR_BUFFER_INSTANCE_0    = 0,
    CIRCULAR_BUFFER_INSTANCE_1,
    CIRCULAR_BUFFER_INSTANCE_2,
    CIRCULAR_BUFFER_INSTANCE_TOTAL,
} circular_buffer_instance_t;

///
/// \breif The circular buffer result type.
///
typedef enum
{
    CIRCULAR_BUFFER_RESULT_SUCCESS          = 0,
    CIRCULAR_BUFFER_RESULT_ERROR            = 1,
    CIRCULAR_BUFFER_RESULT_NULL_POINTER     = 2,
    CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE = 3,
    CIRCULAR_BUFFER_RESULT_EMPTY            = 4,
} circular_buffer_result_t;

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
///
/// \biref Clear the circular buffer instance.
///
/// \param[in] instance The instance of the circular buffer data structure.
///
/// \return circular_buffer_result_t       Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS On success.
/// \retval CIRCULAR_BUFFER_RESULT_ERROR   Otherwise.
///
circular_buffer_result_t circular_buffer_clear(circular_buffer_instance_t instance);

///
/// \biref Clear all of the cicrular buffer instances.
///
/// \return circular_buffer_result_t       Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS On success.
/// \retval CIRCULAR_BUFFER_RESULT_ERROR   Otherwise.
///
circular_buffer_result_t circular_buffer_clear_all(void);

///
/// \biref Push the element to given instance of the circular buffer.
///
/// \param[in] instance The instance of the circular buffer data structure.
/// \param[in] element  The element which will be pushed to ciruclar buffer.
///
/// \return circular_buffer_result_t       Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS On success.
/// \retval CIRCULAR_BUFFER_RESULT_ERROR   Otherwise.
///
circular_buffer_result_t circular_buffer_push(circular_buffer_instance_t instance, uint8_t element);

///
/// \biref Pop the oldest element from given instance of the circular buffer.
///
/// \param[in]  instance The instance of the circular buffer data structure.
/// \param[out] element  The address where the element will be placed.
///
/// \return circular_buffer_result_t       Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS On success.
/// \retval CIRCULAR_BUFFER_RESULT_ERROR   Otherwise.
///
circular_buffer_result_t circular_buffer_pop(circular_buffer_instance_t instance, uint8_t *element);

#endif /* _CIRCULAR_BUFFER_H */
