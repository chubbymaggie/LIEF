/* Copyright 2017 R. Thomas
 * Copyright 2017 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "pyPE.hpp"

#include "LIEF/PE/hash.hpp"
#include "LIEF/PE/resources/ResourceVarFileInfo.hpp"

#include <string>
#include <sstream>


template<class T>
using getter_t = T (ResourceVarFileInfo::*)(void) const;

template<class T>
using setter_t = void (ResourceVarFileInfo::*)(T);

void init_PE_ResourceVarFileInfo_class(py::module& m) {
  py::class_<ResourceVarFileInfo, LIEF::Object>(m, "ResourceVarFileInfo",
      "This object describes information about languages supported by the application")

    .def_property("type",
        static_cast<getter_t<uint16_t>>(&ResourceVarFileInfo::type),
        static_cast<setter_t<uint16_t>>(&ResourceVarFileInfo::type),
        "The type of data in the version resource\n\n"
        "* ``1`` if it contains text data\n"
        "* ``0`` if it contains binary data\n")

    .def_property("key",
        static_cast<getter_t<const std::u16string&>>(&ResourceVarFileInfo::key),
        static_cast<setter_t<const std::string&>>(&ResourceVarFileInfo::key),
        "Signature of the structure. Must be ``VarFileInfo``")

    .def_property("translations",
        static_cast<std::vector<uint32_t>& (ResourceVarFileInfo::*)(void)>(&ResourceVarFileInfo::translations),
        static_cast<setter_t<const std::vector<uint32_t>&>>(&ResourceVarFileInfo::translations),
        "List of languages that the application supports\n\n"
        "The **least** significant 16-bits  must contain a Microsoft language identifier, "
        "and the **most** significant 16-bits must contain the " RST_CLASS_REF(lief.PE.CODE_PAGES) "\n"
        "Either **most** or **least** 16-bits can be zero, indicating that the file is "
        "language or code page independent.")

    .def("__eq__", &ResourceVarFileInfo::operator==)
    .def("__ne__", &ResourceVarFileInfo::operator!=)
    .def("__hash__",
        [] (const ResourceVarFileInfo& var_file_info) {
          return Hash::hash(var_file_info);
        })

    .def("__str__",
        [] (const ResourceVarFileInfo& var_file_info) {
          std::ostringstream stream;
          stream << var_file_info;
          std::string str = stream.str();
          return str;
        });
}

