# -*- cmake -*-
include(Prebuilt)

if (STANDALONE)
  set(BREAKPAD_EXCEPTION_HANDLER_FIND_REQUIRED ON)
  include(FindGoogleBreakpad)
else (STANDALONE)
  use_prebuilt_binary(google_breakpad)
  if (DARWIN)
    set(BREAKPAD_EXCEPTION_HANDLER_LIBRARIES exception_handler)
  endif (DARWIN)
  if (LINUX)
    set(BREAKPAD_EXCEPTION_HANDLER_LIBRARIES breakpad_client)
  endif (LINUX)
  if (WINDOWS)
    set(BREAKPAD_EXCEPTION_HANDLER_LIBRARIES exception_handler crash_generation_client crash_generation_server common)
  endif (WINDOWS)
  # yes, this does look dumb, no, it's not incorrect
  # I think it's incorrect: the second one should go --Aleric
  set(BREAKPAD_INCLUDE_DIRECTORIES "${LIBS_PREBUILT_DIR}/${LL_ARCH_DIR}/include/google_breakpad" "${LIBS_PREBUILT_DIR}/${LL_ARCH_DIR}/include/google_breakpad/google_breakpad")
endif (STANDALONE)
