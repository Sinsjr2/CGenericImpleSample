typedef struct {
    void* entriesValue;
    void* entriesKey;
    bool* entriesHasValue;
    size_t keySize;
    size_t valueSize;
    size_t entriesLength;
    /* must be power of 2 */
    size_t entriesCapacity;

    getHashCode;
    equalsKey;
} il2c_Dictionary;

void il2c_dic_set(il2c_Dictionary* dic, const void* key, const void* value);
// if not found return NULL.
void* il2c_dic_getValue(il2c_Dictionary* dic, const void* key);
/* freeKey and freeValue can be null. */
void il2c_dic_maybeFreeElements(bool* hasValues, uint8_t* elements, size_t elementSize, size_t elementsLength, freeElement);

static void il2c_dic_set_unsafe(il2c_Dictionary* dic, void* key, void* value) {
    // div by power of 2
    size_t divValue = dic->entriesCapacity - 1;
    size_t index = dic->getHashCode(key) & divValue;

    // search index
    for (; !dic->entriesHasValue[index] || dic->equalsKey(dic->entriesKey[index], key) ; index = (index + 1) & divValue);

    memcpy(&dic->entriesKey, key, dic->keySize);
    memcpy(&dic->entriesValue[index], value, dic->valueSize);
    dic->entriesHasValue[index] = true;
}

static void il2c_dic_maybeFreeElements(bool* hasValues, uint8_t* elements, size_t elementSize, size_t elementsLength, freeElement) {
    if (freeElement != NULL) {
        size_t end = elementSize * elementsLength;
        for (size_t i = 0; i < end; i += elementSize) {
            if (hasValues[i]) {
                freeElement(&elements[i]);
            }
        }
    }
}

void il2c_dic_destroy(il2c_Dictionary* dic, freeKey, freeValue) {
    il2c_dic_maybeFreeElements(dic->entriesHasValue, dic->entriesKey, dic->keySize, dic->entriesCapacity, freeKey);
    il2c_dic_maybeFreeElements(dic->entriesHasValue, dic->entriesValue, dic->valueSize, dic->entriesCapacity, freeValue);
    il2c_free(dic->entriesValue);
}

void il2c_dic_set(il2c_Dictionary* dic, const void* key, const void* value) {
    dic->entriesLength++;

    // expand buffer size;
    if (dic->entriesCapacity < dic->entriesLength) {
        size_t currentCapacity = dic->entriesCapacity;
        size_t nextCapacity = (currentCapacity <= 0 ? 1 : currentCapacity << 1 /* * 2 */);
        uint8_t* values = dic->entriesValue;
        uint8_t* keys = dic->entriesKey;

        size_t mallocSize = (dic->valueSize + dic->keySize) * sizeof(bool) * nextCapacity;
        uint8_t* buf = il2c_malloc(mallocSize);
        memset(buf, 0x00, mallocSize);

        dic->entriesValue = buf;
        dic->entriesKey = &buf[dic->valueSize * nextCapacity];
        dic->entriesHasValue = &buf[(dic->valueSize + dic->keySize) * dic->entriesCapacity];
        dic->entriesCapacity = nextCapacity;

        // entry is full. so no need to check.
        size_t endKey = dic->keySize * currentCapacity;
        for (size_t keyI = 0, valueI = 0; i < endKey; keyI += dic->keySize, valueI += dic->valueSize) {
            il2c_dic_set_unsafe(dic, keys[keyI], values[valueI]);
        }
        il2c_free(dic->entriesValue);
    }

    il2c_dic_set_unsafe(dic, key, value);
}

// if not found return NULL.
void* il2c_dic_getValue(il2c_Dictionary* dic, const void* key, void* result) {
    // div by power of 2
    size_t divValue = dic->entriesCapacity - 1;
    size_t index = dic->getHashCode(key) & divValue;

    for (; dic->entriesHasValue[index] ; index = (index + 1) & divValue) {
        if(dic->equalsKey(dic->entriesKey[index], key)) {
            return &dic->entriesValue[index];
        }
    }
    return NULL;
}
