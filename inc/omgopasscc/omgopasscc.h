#ifndef OMGOPASSCC_H__
#define OMGOPASSCC_H__

#include <cctype>
#include <sstream>
#include <string>
#include <sys/random.h>
#include <vector>

namespace omgopasscc {
    class random_buffer {
        public:

            random_buffer()
                : random_buffer(256)
            {
            }

            random_buffer(size_t sz)
                : __size(sz)
                , __index(0)
            {
                __buffer.resize(__size);
                auto res = getrandom(&__buffer[0], __buffer.size(), 0);
            }

            unsigned char operator()(char limit)
            {
                if (__index >= __size) {
                    auto res = getrandom(&__buffer[0], __buffer.size(), 0);
                    __index = 0;
                }

                return __buffer[__index++] % limit;
            }

        private:

            size_t                     __size;
            std::vector<unsigned char> __buffer;
            size_t                     __index;
    };

    //////////////////////////////////////////////////////////////////////////
    struct config {
            size_t      syllablesCount = 3;
            size_t      minSyllableLength = 2;
            size_t      maxSyllableLength = 3;
            bool        hasNumbers = true;
            bool        titlecased = true;
            std::string separators = "-";
            std::string vowels = "aeiouy";
            std::string consonants = "bcdfghjklmnpqrstvwxz";
    };
    //////////////////////////////////////////////////////////////////////////
    static std::string to_string(const config &cfg)
    {
        std::stringstream ss;

        ss << "syllablesCount=" << cfg.syllablesCount << ", "
           << "minSyllableLength=" << cfg.minSyllableLength << ", "
           << "maxSyllableLength=" << cfg.maxSyllableLength << ", "
           << "hasNumbers=" << ((cfg.hasNumbers) ? "true" : "false") << ", "
           << "titlecased=" << ((cfg.titlecased) ? "true" : "false") << ", "
           << "separators=\"" << cfg.separators << "\", "
           << "vowels=\"" << cfg.vowels << "\", "
           << "consonants=\"" << cfg.consonants << "\"";

        return ss.str();
    }
    //////////////////////////////////////////////////////////////////////////

    static std::string generate(const config &cfg = config())
    {

        random_buffer     random;

        std::stringstream ss;
        for (size_t i = 0; i < cfg.syllablesCount; i++) {

            size_t length =
                cfg.minSyllableLength +
                random(cfg.maxSyllableLength - cfg.minSyllableLength + 1);

            for (size_t j = 0; j < length; j++) {
                auto &alpha = (j % 2) ? cfg.vowels : cfg.consonants;
                char  ch = alpha[random(alpha.size())];

                ss << (char)((cfg.titlecased && !j) ? std::toupper(ch) : ch);
            }

            if (cfg.hasNumbers)
                ss << std::to_string(random(10));

            if (cfg.separators.size() && ((i + 1) != cfg.syllablesCount)) {
                ss << (char)(cfg.separators[random(cfg.separators.size())]);
            }
        }
        return ss.str();
    }
} // namespace omgopasscc

#endif
