execute_process(COMMAND pkg-config gtkmm-3.0 --cflags-only-I
        COMMAND sed "s/-I//g"
        COMMAND sed "s/ /;/g"
        OUTPUT_VARIABLE gtkmm_INCLUDE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(COMMAND pkg-config gtkmm-3.0 --libs 
        COMMAND sed "s/-l//g"
        COMMAND sed "s/ /;/g"
        OUTPUT_VARIABLE gtkmm_LIBRARY
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(gtkmm_LIBRARIES ${gtkmm_LIBRARY})
set(gtkmm_INCLUDE_DIRS ${gtkmm_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# Handle the QUIETLY and REQUIRED arguments and set the gtkmm_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(gtkmm DEFAULT_MSG
                                  gtkmm_LIBRARY gtkmm_INCLUDE_DIR)

mark_as_advanced(gtkmm_INCLUDE_DIR gtkmm_LIBRARY)