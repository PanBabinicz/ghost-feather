#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

#include <stdint.h>
#include <string.h>

#define CIRCULAR_BUFFER_LENGTH  (64U)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \breif The circular buffer instance type.
///
typedef enum
{
    CIRCULAR_BUFFER_INSTANCE_NONE = -1,
    CIRCULAR_BUFFER_INSTANCE_0    =  0,
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
/// \biref Gets the circular buffer content.
///
/// \param[in]  instance    The instance of the circular buffer data structure.
/// \param[out] buffer      The buffer where the content goes to.
/// \param[in]  buffer_size The buffer size.
///
/// \return circular_buffer_result_t                Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS          On success.
/// \retval CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE On invalid instance.
///
circular_buffer_result_t circular_buffer_get_data(const circular_buffer_instance_t instance,
                                                  uint8_t *const buffer, const uint32_t buffer_size);

///
/// \biref Sets the circular buffer content.
///
/// \param[in] instance    The instance of the circular buffer data structure.
/// \param[in] buffer      The buffer where the content goes to.
/// \param[in] buffer_size The buffer size.
///
/// \return circular_buffer_result_t                Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS          On success.
/// \retval CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE On invalid instance.
///
circular_buffer_result_t circular_buffer_set_data(const circular_buffer_instance_t instance,
                                                  const uint8_t *const buffer, const uint32_t buffer_size);

///
/// \biref Sets the circular buffer state.
///
/// \param[in] instance The instance of the circular buffer data structure.
/// \param[in] rear     The buffer where the content goes to.
/// \param[in] front    The buffer size.
/// \param[in] overflow The buffer size.
///
/// \return circular_buffer_result_t                Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS          On success.
/// \retval CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE On invalid instance.
///
circular_buffer_result_t circular_buffer_set_state(const circular_buffer_instance_t instance, const uint8_t rear,
                                                   const uint8_t front, const uint8_t overflow);

///
/// \biref Clears the circular buffer instance.
///
/// \param[in] instance The instance of the circular buffer data structure.
///
/// \return circular_buffer_result_t                Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS          On success.
/// \retval CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE On invalid instance.
///
circular_buffer_result_t circular_buffer_clear(circular_buffer_instance_t instance);

///
/// \biref Clears all of the cicrular buffer instances.
///
/// \return circular_buffer_result_t       Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS On success.
/// \retval CIRCULAR_BUFFER_RESULT_ERROR   Otherwise.
///
circular_buffer_result_t circular_buffer_clear_all(void);

///
/// \biref Pushes the element to given instance of the circular buffer.
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
/// \biref Pops the oldest element from given instance of the circular buffer.
///
/// \param[in]  instance The instance of the circular buffer data structure.
/// \param[out] element  The address where the element will be placed.
///
/// \return circular_buffer_result_t            Result of the function.
/// \retval CIRCULAR_BUFFER_RESULT_SUCCESS      On success.
/// \retval CIRCULAR_BUFFER_RESULT_EMPTY        On empty circular buffer.
/// \retval CIRCULAR_BUFFER_RESULT_NULL_POINTER On null pointer.
///
circular_buffer_result_t circular_buffer_pop(circular_buffer_instance_t instance, uint8_t *element);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _CIRCULAR_BUFFER_H */
