package = "primesieve"
version = "0.1-1"
source = {
   url = "git+https://github.com/kennypm/lua-primesieve.git"
}
description = {
   summary = "Lua bindings for primesieve, a library for fast prime number generation",
   homepage = "https://github.com/kennypm/lua-primesieve",
   license = "MIT"
}
dependencies = {
   "lua >= 5.3"
}
external_dependencies = {
   PRIMESIEVE = {
      library = "primesieve"
   }
}
build = {
   type = "builtin",
   modules = {
      primesieve = {
         incdirs = {
            "$(PRIMESIEVE_INCDIR)"
         },
         libdirs = {
            "$(PRIMESIEVE_LIBDIR)"
         },
         libraries = {
            "primesieve"
         },
         sources = {
            "lua-primesieve.c",
            "array.c",
            "iterator.c"
         }
      }
   }
}
