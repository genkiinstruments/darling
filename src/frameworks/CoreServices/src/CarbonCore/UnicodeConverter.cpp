#include <CoreServices/UnicodeConverter.h>
#include <cstdio>
#include <iconv.h>

OSStatus CreateTextToUnicodeInfo(ConstUnicodeMappingPtr iUnicodeMapping, TextToUnicodeInfo *oTextToUnicodeInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);

    return 0;
}

OSStatus CreateTextToUnicodeInfoByEncoding(TextEncoding iEncoding, TextToUnicodeInfo *oTextToUnicodeInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus CreateUnicodeToTextInfo(ConstUnicodeMappingPtr iUnicodeMapping, UnicodeToTextInfo *oUnicodeToTextInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);

    printf("Encoding: %02x, other encoding: %02x, version: %d\n",
           (unsigned int) iUnicodeMapping->unicodeEncoding,
           (unsigned int) iUnicodeMapping->otherEncoding,
           (unsigned int) iUnicodeMapping->mappingVersion);

    return 0;
}

OSStatus CreateUnicodeToTextInfoByEncoding(TextEncoding iEncoding, UnicodeToTextInfo *oUnicodeToTextInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus CreateUnicodeToTextRunInfo(ItemCount iNumberOfMappings,
                                    const UnicodeMapping iUnicodeMappings[],
                                    UnicodeToTextRunInfo * oUnicodeToTextInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus CreateUnicodeToTextRunInfoByEncoding(ItemCount iNumberOfEncodings,
                                              const TextEncoding iEncodings[],
                                              UnicodeToTextRunInfo *oUnicodeToTextInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus CreateUnicodeToTextRunInfoByScriptCode(ItemCount iNumberOfScriptCodes,
                                                const ScriptCode iScripts[],
                                                UnicodeToTextRunInfo *oUnicodeToTextInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus ChangeTextToUnicodeInfo(TextToUnicodeInfo ioTextToUnicodeInfo, ConstUnicodeMappingPtr iUnicodeMapping)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus ChangeUnicodeToTextInfo(UnicodeToTextInfo ioUnicodeToTextInfo, ConstUnicodeMappingPtr iUnicodeMapping)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus DisposeTextToUnicodeInfo(TextToUnicodeInfo *ioTextToUnicodeInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus DisposeUnicodeToTextInfo(UnicodeToTextInfo *ioUnicodeToTextInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus DisposeUnicodeToTextRunInfo(UnicodeToTextRunInfo * ioUnicodeToTextRunInfo)
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus ConvertFromTextToUnicode(TextToUnicodeInfo iTextToUnicodeInfo,
                                  ByteCount iSourceLen,
                                  ConstLogicalAddress iSourceStr,
                                  OptionBits iControlFlags,
                                  ItemCount iOffsetCount,
                                  const ByteOffset iOffsetArray[],
                                  ItemCount *oOffsetCount,
                                  ByteOffset oOffsetArray[],
                                  ByteCount iOutputBufLen,
                                  ByteCount *oSourceRead,
                                  ByteCount *oUnicodeLen,
                                  UniChar oUnicodeStr[])
{
    printf("STUB %s\n", __PRETTY_FUNCTION__);
    return 0;
}

OSStatus ConvertFromUnicodeToText(UnicodeToTextInfo iUnicodeToTextInfo,
                                  ByteCount iUnicodeLen,
                                  const UniChar iUnicodeStr[],
                                  OptionBits iControlFlags,
                                  ItemCount iOffsetCount,
                                  const ByteOffset iOffsetArray[],
                                  ItemCount *oOffsetCount,
                                  ByteOffset oOffsetArray[],
                                  ByteCount iOutputBufLen,
                                  ByteCount *oInputRead,
                                  ByteCount *oOutputLen,
                                  LogicalAddress oOutputStr)
{
    // TODO: Take into account other to/from encodings
    iconv_t cd = iconv_open("ISO-8859-1", "UTF-8");
    if (cd == reinterpret_cast<iconv_t>(-1))
    {
        printf("iconv result: %p\n", cd);
        return -1;
    }

    auto* input = reinterpret_cast<char *>(const_cast<UniChar *>(iUnicodeStr));
    auto* output = reinterpret_cast<char *>(oOutputStr);
    size_t input_len = iUnicodeLen;
    size_t output_len = iOutputBufLen;

    const auto result = iconv(cd, &input, &input_len, &output, &output_len);

    if (result == static_cast<size_t>(-1)) {
        printf("iconv conversion failed: %lu\n", result);
        iconv_close(cd);
        return -1;
    }

    *oOutputLen = iOutputBufLen - output_len;
    iconv_close(cd);

    return noErr;
}
