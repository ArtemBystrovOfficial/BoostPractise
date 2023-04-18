
#include <iostream>
#include <boost/stacktrace/stacktrace_fwd.hpp>
#include <boost/stacktrace.hpp>
#include <iosfwd>

namespace boost {
    namespace stacktrace {

        template <class CharT, class TraitsT, class Allocator>
        std::basic_ostream<CharT, TraitsT>& do_stream_st(std::basic_ostream<CharT, TraitsT>& os, const basic_stacktrace<Allocator>& bt);

        template <class CharT, class TraitsT>
        std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& os, const stacktrace& bt) {
            return do_stream_st(os, bt);
        }

        template <class CharT, class TraitsT, class Allocator>
        std::basic_ostream<CharT, TraitsT>& do_stream_st(std::basic_ostream<CharT, TraitsT>& os, const basic_stacktrace<Allocator>& bt) {
            const std::streamsize w = os.width();
            const std::size_t frames = bt.size();
            for (std::size_t i = 0; i < frames; ++i) {
                os.width(2);
                os << i;
                os.width(w);
                os << "# ";
                os << bt[i].name();
                os << '\n';
            }

            return os;
        }
    }

}  // namespace boost::stacktrace

void foo() {
    std::cout << boost::stacktrace::stacktrace();
}

int main() {
    foo();
}

