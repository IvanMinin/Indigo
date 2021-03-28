/****************************************************************************
 * Copyright (C) from 2009 to Present EPAM Systems.
 *
 * This file is part of Indigo toolkit.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***************************************************************************/

#ifndef __structure_checker__
#define __structure_checker__

#include <sstream>

#include "base_cpp/exception.h"
#include "base_cpp/red_black.h"
#include "base_cpp/obj_array.h"
#include "base_cpp/output.h"
#include "base_cpp/scanner.h"
#include "molecule/elements.h"
#include "molecule/molecule.h"
#include "molecule/molecule_automorphism_search.h"
#include "molecule/query_molecule.h"

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


namespace indigo
{

    class Molecule;
    class QueryMolecule;
    class BaseMolecule;
    class Scanner;
    class Output;

    class DLLEXPORT StructureChecker
    {
    public:
        enum
        {
            // Check types
            CHECK_NONE = 0x00000,         // Check none
            CHECK_LOAD = 0x00001,         // Check loading (correspondence some known format)
            CHECK_VALENCE = 0x00002,      // Check valence correctness
            CHECK_RADICAL = 0x00004,      // Check radicals existance
            CHECK_PSEUDOATOM = 0x00008,   // Check pseudoatoms existance
            CHECK_STEREO = 0x00010,       // Check strerochemistry description correctness
            CHECK_QUERY = 0x00020,        // Check query fetaures existance
            CHECK_OVERLAP_ATOM = 0x00040, // Check overlapping atoms existance
            CHECK_OVERLAP_BOND = 0x00080, // Check overlapping bonds existance
            CHECK_RGROUP = 0x00100,       // Check R-groups existance
            CHECK_SGROUP = 0x00200,       // Check S-groups existance
            CHECK_TGROUP = 0x00400,       // Check T-groups existance (SCSR features)
            CHECK_CHIRALITY = 0x00800,    // Check chirality feature correctness (including 3D source)
            CHECK_CHIRAL_FLAG = 0x01000,  // Check chiral flag existance (MOLFILE format)
            CHECK_3D_COORD = 0x02000,     // Check 3D coordinates existance
            CHECK_CHARGE = 0x04000,       // Check charged structure
            CHECK_SALT = 0x08000,         // Check possible salt structure
            CHECK_AMBIGUOUS_H = 0x10000,  // Check ambiguous H existance
            CHECK_COORD = 0x20000,        // Check coordinates existance
            CHECK_ALL = 0xFFFF           // Check all features
        };

        enum
        {
            // Check severity level
            CHECK_INFO = 1, // Information message
            CHECK_WARINING, // Warning message
            CHECK_ERROR     // Error message
        };

        enum
        {
            // Check messages
            CHECK_MSG_LOAD = 1,
            CHECK_MSG_VALENCE,
            CHECK_MSG_IGNORE_VALENCE_ERROR,
            CHECK_MSG_RADICAL,
            CHECK_MSG_PSEUDOATOM,
            CHECK_MSG_CHIRAL_FLAG,
            CHECK_MSG_WRONG_STEREO,
            CHECK_MSG_3D_STEREO,
            CHECK_MSG_UNDEFINED_STEREO,
            CHECK_MSG_IGNORE_STEREO_ERROR,
            CHECK_MSG_QUERY,
            CHECK_MSG_IGNORE_QUERY_FEATURE,
            CHECK_MSG_OVERLAP_ATOM,
            CHECK_MSG_OVERLAP_BOND,
            CHECK_MSG_RGROUP,
            CHECK_MSG_SGROUP,
            CHECK_MSG_TGROUP,
            CHECK_MSG_CHARGE,
            CHECK_MSG_SALT,
            CHECK_MSG_EMPTY,
            CHECK_MSG_AMBIGUOUS_H,
            CHECK_MSG_3D_COORD,
            CHECK_MSG_ZERO_COORD
        };

        enum
        {
            BAD_VALENCE = 100,
            BAD_RADICAL
        };

        struct CheckType
        {
            bool compare(const char* text) const;

            const char* t_text;
            dword t_flag;
        };

        struct CheckMessage
        {
            int m_id;
            dword m_flag;
            const char* m_text;
        };

        struct CheckResult
        {
            int m_id;
            Array<int> atom_ids;
            Array<int> bond_ids;
        };

        StructureChecker(Output& output);

        void checkStructure(Scanner& scanner, const char* params);

        void checkBaseMolecule(BaseMolecule& mol);
        void checkMolecule(Molecule& mol);
        void checkQueryMolecule(QueryMolecule& mol);

        void checkMolecule(BaseMolecule& mol, bool query);

        void parseCheckTypes(const char* params);
        void addAtomSelection(Array<int>& atoms);
        void addBondSelection(Array<int>& bonds);

        void buildCheckResult();

        void clearCheckResult();

        static const char* typeToString(dword check_type);
        static dword getType(const char* check_type);

        dword check_flags;
        dword check_result;

        float mean_dist;

        DECL_ERROR;

    protected:
        void _parseSelection(Scanner& sc, Array<int>& ids);
        void _checkAtom(BaseMolecule& mol, Molecule& target, int idx, bool query);
        void _checkBond(BaseMolecule& mol, Molecule& target, int idx, bool query);

        Array<int> _selected_atoms;
        Array<int> _selected_bonds;

        ObjArray<CheckResult> _results;

        Array<int> _bad_val_ids;
        Array<int> _rad_ids;
        Array<int> _atom_qf_ids;
        Array<int> _bond_qf_ids;
        Array<int> _pseudo_ids;
        Array<int> _sg_atom_ids;
        Array<int> _sg_bond_ids;
        Array<int> _atom_3d_ids;
        Array<int> _overlapped_atom_ids;
        Array<int> _overlapped_bond_ids;
        Array<int> _atom_amb_h_ids;
        Array<int> _atom_3d_stereo_ids;
        Array<int> _atom_wrong_stereo_ids;
        Array<int> _atom_undefined_stereo_ids;

        Output& _output;

    private:
        StructureChecker(const StructureChecker&); // no implicit copy
    };

} // namespace indigo

#endif
