/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file huffmanTable.h
    \brief Declaration of the huffman codec

*/

#if !defined(imebraHuffmanTable_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraHuffmanTable_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include <memory>
#include <vector>
#include <map>
#include <array>
#include <limits>


namespace imebra
{

namespace implementation
{

namespace codecs
{
class jpegStreamReader;
}

class streamWriter;

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class calculates the huffman table from
///         a set of values and their frequency, and
///         can read or write huffman codes from/to a
///         baseStream object.
///
///////////////////////////////////////////////////////////
class huffmanTable
{
public:
    ///////////////////////////////////////////////////////////
    /// \name Initialization
    ///
    ///////////////////////////////////////////////////////////
    //@{

    /// \brief Construct the huffman table and specify the
    ///         maximum numbed of bits used by the values to
    ///         be encoded.
    ///
    /// @param maxValueLength the maximum lenght, in bits, of
    ///                        the value that must be encoded.
    ///                       Please note that this is not
    ///                        the length of the huffman values
    ///
    ///////////////////////////////////////////////////////////
    huffmanTable(std::uint32_t maxValueLength);

    /// \brief Reset the internal data of the huffmanTable
    ///         class.
    ///
    /// The function removes all the calculated tables.
    /// The I/O functions readHuffmanCode() and
    ///  writeHuffmanCode() will not work until the tables are
    ///  calculated by calcHuffmanCodesLength and
    ///  calcHuffmanTables().
    ///
    ///////////////////////////////////////////////////////////
    void reset();

    //@}


    ///////////////////////////////////////////////////////////
    /// \name Huffman table generation
    ///
    /// First, call incValueFreq() the right number of times
    ///  for each value that appears in the stream, then
    ///  call calcHuffmanCodesLength() and then
    ///  calcHuffmanTables().
    ///
    ///////////////////////////////////////////////////////////
    //@{

    /// \brief Increase the frequency of a value that will be
    ///         huffman encoded.
    ///
    /// This function must be called for each time a value
    ///  appears in a stream. Values with an higher frequency
    ///  will have a shorted huffman code.
    ///
    /// After the function has been called the right amount of
    ///  times for every value that must be encoded, call
    ///  calcHuffmanCodesLength() and then calcHuffmanTables().
    ///
    /// @param value   the value for wich the frequency must
    ///                 be increased.
    ///                The number of bits that form the value
    ///                 must be less or equal to the number
    ///                 of bits specified in the constructor
    ///                 huffmanTable()
    ///
    ///////////////////////////////////////////////////////////
    void incValueFreq(const std::uint32_t value);

    /// \brief Calculates the length of the huffman codes.
    ///
    /// This function must be called after incValueFreq() has
    ///  been called to set the frequency of the values to be
    ///  encoded.
    ///
    /// After this function calculates the codes length, call
    ///  calcHuffmanTables() to calculate the huffman codes
    ///  used by readHuffmanCode() and writeHuffmanCode().
    ///
    /// @param maxCodeLength the maximum length in bits of the
    ///                       generated huffman codes.
    ///
    ///////////////////////////////////////////////////////////
    void calcHuffmanCodesLength(const std::uint32_t maxCodeLength);

    /// \brief Generates the huffman table used by
    ///         readHuffmanCode() and writeHuffmanCode().
    ///
    /// This function need the codes length generated by
    ///  calcHuffmanCodesLength(): it will not work if the
    ///  code lengths are not available.
    ///
    ///////////////////////////////////////////////////////////
    void calcHuffmanTables();

    /// \brief Remove the code with the higher value and the
    ///         longer code from the code lengths table.
    ///
    /// This function is usefull when extra data has been
    ///  inserted through incValueFreq() but must not generate
    ///  an huffman code.
    ///
    /// E.g.: the jpeg coded insert an extra value with low
    ///       frequency to reserve the last generated huffman
    ///       code, so the reserver huffman code will never
    ///       be generated
    ///
    ///////////////////////////////////////////////////////////
    void removeLastCode();

    void setValuesPerLength(std::uint32_t length, std::uint32_t numValues);
    void addOrderedValue(size_t index, std::uint32_t value);

    std::uint32_t getValuesPerLength(std::uint32_t length);
    std::uint32_t getOrderedValue(size_t index);

    //@}


    ///////////////////////////////////////////////////////////
    /// \name Huffman I/O
    ///
    ///////////////////////////////////////////////////////////
    //@{

    /// \brief Read and decode an huffman code from the
    ///         specified stream.
    ///
    /// The function throws a huffmanExceptionRead exception
    ///  if the read code cannot be decoded.
    ///
    /// @param stream  the stream reader used to read the code
        /// @return the decoded value
    ///
    ///////////////////////////////////////////////////////////
    std::uint32_t readHuffmanCode(codecs::jpegStreamReader& stream);

    /// \brief Write an huffman code to the specified stream.
    ///
    /// The function throws a huffmanExceptionWrite exception
    ///  if the specified value cannot be encoded.
    ///
    /// @param code     the value to be encoded and written to
    ///                  the stream
    /// @param pStream  a pointer to the stream writer used to
    ///                  write the code
    ///
    ///////////////////////////////////////////////////////////
    void writeHuffmanCode(const std::uint32_t code, streamWriter* pStream);

    //@}

protected:
    class valueObject
    {
    public:
        valueObject():m_freq(0), m_codeLength(0), m_nextCode(std::numeric_limits<std::uint32_t>::max()){}
        valueObject(const valueObject& right):m_freq(right.m_freq), m_codeLength(right.m_codeLength), m_nextCode(right.m_nextCode){}
        std::uint32_t m_freq;
        std::uint32_t m_codeLength;
        std::uint32_t m_nextCode;
    };

    class freqValue
    {
    public:
        freqValue(std::uint32_t freq = 0, std::uint32_t value = 0):m_freq(freq), m_value(value){}
        freqValue(const freqValue& right):m_freq(right.m_freq), m_value(right.m_value){}

        std::uint32_t m_freq;
        std::uint32_t m_value;
    };
    struct freqValueCompare
    {
                bool operator()(const freqValue& left, const freqValue& right) const
        {
            return left.m_freq < right.m_freq || (left.m_freq == right.m_freq && left.m_value > right.m_value);
        }
    };

    class lengthValue
    {
    public:
        lengthValue(std::uint32_t length = 0, std::uint32_t value = 0):m_length(length), m_value(value){}
        lengthValue(const lengthValue& right):m_length(right.m_length), m_value(right.m_value){}

        std::uint32_t m_length;
        std::uint32_t m_value;
    };
    struct lengthValueCompare
    {
                bool operator()(const lengthValue& left, const lengthValue& right) const
        {
            return left.m_length < right.m_length || (left.m_length == right.m_length && left.m_value < right.m_value);
        }
    };

    std::uint32_t m_numValues;

    // Values' frequency
    std::vector<valueObject> m_valuesFreq;

private:
    // Used to calculate the huffman codes
    std::vector<std::uint32_t> m_orderedValues;
    std::array<std::uint32_t, 128> m_valuesPerLength;
    size_t m_firstValidLength;
    std::uint32_t m_firstMinValue;
    std::uint32_t m_firstMaxValue;
    std::uint32_t m_firstValuesPerLength;
    std::uint32_t m_minValuePerLength[128];
    std::uint32_t m_maxValuePerLength[128];

    // Final huffman table
    std::vector<std::uint32_t> m_valuesToHuffman;
    std::vector<size_t> m_valuesToHuffmanLength;

};

} // namespace implementation

} // namespace imebra


#endif // !defined(imebraHuffmanTable_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
