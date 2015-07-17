from libcpp.string cimport string
from libc.string cimport const_char

ctypedef void (*callback_t)(size_t a, size_t b, void* user_data)
        
cdef extern from "dictionary/dictionary_types.h" namespace "keyvi::dictionary":
    cdef cppclass CompletionDictionaryCompiler:
        CompletionDictionaryCompiler() except +
        CompletionDictionaryCompiler(size_t memory_limit) except +
        void Add(const_char*, int) except +
        void __setitem__ (const_char*, int) except +
        void Compile() nogil # wrap-ignore
        void Compile(callback_t, void*) nogil # wrap-ignore
        void WriteToFile(const_char*)
        
    cdef cppclass CompletionDictionaryCompilerCompact:
        CompletionDictionaryCompilerCompact() except +
        CompletionDictionaryCompilerCompact(size_t memory_limit) except +
        void Add(const_char*, int) except +
        void __setitem__ (const_char*, int) except +
        void Compile() nogil # wrap-ignore
        void Compile(callback_t, void*) nogil # wrap-ignore
        void WriteToFile(const_char*)

    cdef cppclass KeyOnlyDictionaryCompiler:
        KeyOnlyDictionaryCompiler() except +
        KeyOnlyDictionaryCompiler(size_t memory_limit) except +
        void Add(const_char*) except +
        void Compile() nogil # wrap-ignore
        void Compile(callback_t, void*) nogil # wrap-ignore
        void WriteToFile(const_char*)
        
    cdef cppclass JsonDictionaryCompilerCompact:
        JsonDictionaryCompilerCompact() except +
        JsonDictionaryCompilerCompact(size_t memory_limit) except +
        void Add(const_char*, const_char*) except +
        void __setitem__(const_char*, const_char*) except +
        void Compile() nogil # wrap-ignore
        void Compile(callback_t, void*) nogil # wrap-ignore
        void WriteToFile(const_char*)
    
    cdef cppclass StringDictionaryCompilerCompact:
        StringDictionaryCompilerCompact() except +
        StringDictionaryCompilerCompact(size_t memory_limit) except +
        void Add(const_char*, const_char*) except +
        void __setitem__(const_char*, const_char*) except +
        void Compile() nogil # wrap-ignore
        void Compile(callback_t, void*) nogil # wrap-ignore
        void WriteToFile(const_char*)
