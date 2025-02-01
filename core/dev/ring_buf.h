

#ifndef _FILE_RING_BUF_H_
#define _FILE_RING_BUF_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifndef RINGBUF_NULL_RET
#define RINGBUF_NULL_RET ((-1))
#endif // RINGBUF_NULL_RET

    //
    // main function summary
    // + init create a ringbuffer object
    // + peek get the current buffer item, -1 if no object in this buffer
    // + put  push a item in this buffer, -1 if the array is full, 0 if operation done completely
    // + get_spare_size get ring buffer spare size
    // + get_valid size get ring buffer valid size
    //

    // basic memory topology
    // 0 | 1 | 2 | 3 | 4 | 5
    //     ^ i get: read number here
    //                 ^ i set: set number here

    // Ring Buffer
    typedef struct _tag_ringbuf_t
    {
        // buffer
        data_gt *buf;
        // length of buffer, the maximum length is `size - 1`
        size_gt size;

        // the position to read
        size_gt iget;
        // the write position
        size_gt iset;
    } ringbuf_t;

    void gmp_init_ringbuf(ringbuf_t *buf, data_gt *content, size_gt size);

// Internal functions
#define JUDGE_IF_RINGBUF_IS_NULL                                                                                       \
    if (buf->iget == buf->iset)                                                                                        \
        return RINGBUF_NULL_RET;

#define WARP_RINGBUF_IGET_POS                                                                                          \
    if (buf->iget >= buf->size)                                                                                        \
        buf->iget = 0;

#define WARP_RINGBUF_ISET_POS                                                                                          \
    if (buf->iget >= buf->size)                                                                                        \
        buf->iset = 0;

    GMP_STATIC_INLINE
    int32_t ringbuf_get_item(ringbuf_t *buf)
    {
        // buffer is null
        JUDGE_IF_RINGBUF_IS_NULL;

        // get target
#if GMP_PORT_DATA_SIZE_PER_BYTES == 1
        data_gt v = buf->buf[buf->iget++];
#elif GMP_PORT_DATA_SIZE_PER_BYTES == 2
    data_gt v = buf->buf[buf->iget++];
#else
#error("GMP_PORT_DATA_SIZE_PER_BYTES is a unknown setting.\r\n")
#endif // GMP_PORT_DATA_SIZE_PER_BYTES

        WARP_RINGBUF_IGET_POS;

        return v;
    }

    GMP_STATIC_INLINE
    int32_t ringbuf_peek_item(ringbuf_t *buf)
    {
        JUDGE_IF_RINGBUF_IS_NULL;

        return buf->buf[buf->iget];
    }

    GMP_STATIC_INLINE
    int32_t ringbuf_peek_last_item(ringbuf_t *buf)
    {
        JUDGE_IF_RINGBUF_IS_NULL;

        size_gt iset_true;

        if (buf->iset == 0)
            iset_true = buf->size - 1;
        else
            iset_true = buf->iset - 1;

        return buf->buf[iset_true];
    }

    // push an item into the buffer
    // if the buffer is full, discard the lastest data.
    GMP_STATIC_INLINE
    fast16_gt ringbuf_put_item(ringbuf_t *buf, data_gt v)
    {
        size_gt iset_new = buf->iset + 1;
        if (iset_new >= buf->size)
        {
            iset_new = 0;
        }
        // buffer has full
        if (iset_new == buf->iget)
        {
            return -1;
        }
        buf->buf[buf->iset] = v;
        buf->iset = iset_new;
        return 0;
    }

    // push an item.
    // if the ring buffer is full discard the oldest data.
    GMP_STATIC_INLINE
    fast16_gt ringbuf_put_item_warp(ringbuf_t *buf, data_gt v)
    {
        fast16_gt ret = 0;
        size_gt iset_new = buf->iset + 1;
        if (iset_new >= buf->size)
        {
            iset_new = 0;
        }
        // buffer has full
        if (iset_new == buf->iget)
        {
            buf->iget += 1;
            buf->iget = buf->iget % buf->size;
            ret = 0;
        }
        buf->buf[buf->iset] = v;
        buf->iset = iset_new;
        return 0;
    }

    GMP_STATIC_INLINE
    size_gt ringbuf_get_spare_size(ringbuf_t *buf)
    {
        return (buf->size + buf->iget - buf->iset - 1) % buf->size;
    }

    GMP_STATIC_INLINE
    size_gt ringbuf_get_valid_size(ringbuf_t *buf)
    {
        return (buf->size + buf->iset - buf->iget) % buf->size;
    }

    GMP_STATIC_INLINE
    void ringbuf_memcpy_get_internal(ringbuf_t *buf, data_gt *data, size_t data_len)
    {
        // No bounds / space checking is performed here so ensure available size is checked before running this
        // otherwise data loss or buffer overflow can occur.
        uint32_t iget = buf->iget;
        uint32_t iget_a = (iget + data_len) % buf->size;
        data_gt *datap = data;
        if (iget_a < iget)
        {
            // Copy part of the data from the space left at the end of the buffer
            memcpy(datap, buf->buf + iget, buf->size - iget);
            datap += (buf->size - iget);
            iget = 0;
        }
        memcpy(datap, buf->buf + iget, iget_a - iget);
        buf->iget = iget_a;
    }

    // Returns:
    //    0: Success
    //   -1: Not enough data available to complete read (try again later)
    //   -2: Requested read is larger than buffer - will never succeed
    GMP_STATIC_INLINE
    fast16_gt ringbuf_get_array(ringbuf_t *buf, data_gt *data, size_gt data_len)
    {
        // special case
        if (data_len == 0)
            return 0;

        if (ringbuf_get_valid_size(buf) < data_len)
        {
            return (buf->size <= data_len) ? -2 : -1;
        }

        ringbuf_memcpy_get_internal(buf, data, data_len);
        return 0;
    }

    GMP_STATIC_INLINE
    void ringbuf_memcpy_put_internal(ringbuf_t *buf, const data_gt *data, size_t data_len)
    {
        // No bounds / space checking is performed here so ensure free size is checked before running this
        // otherwise data loss or buffer overflow can occur.
        uint32_t iput = buf->iset;
        uint32_t iput_a = (iput + data_len) % buf->size;
        const data_gt *datap = data;
        if (iput_a < iput)
        {
            // Copy part of the data to the end of the buffer
            memcpy(buf->buf + iput, datap, buf->size - iput);
            datap += (buf->size - iput);
            iput = 0;
        }
        memcpy(buf->buf + iput, datap, iput_a - iput);
        buf->iset = iput_a;
    }

    // Returns:
    //    0: Success
    //    1: Not enough data available to complete read (try again later)
    //    2: Requested read is larger than buffer - will never succeed
    GMP_STATIC_INLINE
    fast_gt ringbuf_put_array(ringbuf_t *buf, data_gt *data, size_gt data_len)
    {
        // special case
        if (data_len == 0)
            return 0;

        if (ringbuf_get_spare_size(buf) < data_len)
        {
            return (buf->size <= data_len) ? 2 : 1;
        }
        ringbuf_memcpy_put_internal(buf, data, data_len);
        return 0;
    }

    GMP_STATIC_INLINE
    int32_t ringbuf_peek16(ringbuf_t *buf)
    {
        // buffer is null
        JUDGE_IF_RINGBUF_IS_NULL;

#if GMP_PORT_DATA_SIZE_PER_BYTES == 1
        uint32_t iget_a = buf->iget + 1;
        if (iget_a == buf->size)
        {
            iget_a = 0;
        }
        if (iget_a == buf->iset)
        {
            return -1;
        }
        return (buf->buf[buf->iget] << 8) | (buf->buf[iget_a]);
#elif GMP_PORT_DATA_SIZE_PER_BYTES == 2
    return buf->buf[buf->iget];
#else
#error("GMP_PORT_DATA_SIZE_PER_BYTES is a unknown setting.\r\n")
#endif // GMP_PORT_DATA_SIZE_PER_BYTES
    }

    // Note: big-endian. No-op if not enough room available for both bytes.
    GMP_STATIC_INLINE
    int32_t ringbuf_get16(ringbuf_t *buf)
    {
        // get the target value
        int v = ringbuf_peek16(buf);

        if (v == -1)
        {
            return v;
        }

#if GMP_PORT_DATA_SIZE_PER_BYTES == 1
        buf->iget += 2;
#elif GMP_PORT_DATA_SIZE_PER_BYTES == 2
    buf->iget += 1;
#else
#error("GMP_PORT_DATA_SIZE_PER_BYTES is a unknown setting.\r\n")
#endif // GMP_PORT_DATA_SIZE_PER_BYTES

        if (buf->iget >= buf->size)
        {
            buf->iget -= buf->size;
        }
        return v;
    }

    GMP_STATIC_INLINE
    int32_t ringbuf_put16(ringbuf_t *buf, uint16_t v)
    {
        size_gt iput_a = buf->iset + 1;

        if (iput_a == buf->size)
        {
            iput_a = 0;
        }
        if (iput_a == buf->iget)
        {
            return -1;
        }

#if GMP_PORT_DATA_SIZE_PER_BYTES == 1
        size_gt iput_b = iput_a + 1;
        if (iput_b == buf->size)
        {
            iput_b = 0;
        }
        if (iput_b == buf->iget)
        {
            return -1;
        }

        buf->buf[buf->iset] = (v >> 8) & 0xff;
        buf->buf[iput_a] = v & 0xff;
        buf->iset = iput_b;
#elif GMP_PORT_DATA_SIZE_PER_BYTES == 2
    buf->buf[iput_a] = v;
    buf->iset = iput_a;
#else
#error("GMP_PORT_DATA_SIZE_PER_BYTES is a unknown setting.\r\n")
#endif // GMP_PORT_DATA_SIZE_PER_BYTES

        return 0;
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_RING_BUF_H_
