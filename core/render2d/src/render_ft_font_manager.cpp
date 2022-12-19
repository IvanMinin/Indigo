#include "render_ft_font_manager.h"

#include "sans_regular.h"
#include "sans_bold.h"
#include "sans_italic.h"
#include "sans_bold_italic.h"

#include <stdexcept>

namespace indigo
{
    RenderFTFontManager::RenderFTFontManager()
    {
        loadFontFaces();
    }
    
    RenderFTFontManager::~RenderFTFontManager()
    {
        cairo_font_face_destroy (_cairoFaceRegular);
        cairo_font_face_destroy (_cairoFaceBold);
        cairo_font_face_destroy (_cairoFaceItalic);
        cairo_font_face_destroy (_cairoFaceBoldItalic);
    }

    cairo_font_face_t* RenderFTFontManager::selectCairoFontFace(bool isBold, bool isItalic)
    {
        if (isBold && isItalic) {
            return _cairoFaceBoldItalic;
        } else if (isBold) {
            return _cairoFaceBold;
        } else if (isItalic) {
            return _cairoFaceItalic;
        } else {
            return _cairoFaceRegular;
        }
    }

    FT_Face RenderFTFontManager::selectFontFace(bool isBold, bool isItalic)
    {
        if (isBold && isItalic) {
            return _faceBoldItalic;
        } else if (isBold) {
            return _faceBold;
        } else if (isItalic) {
            return _faceItalic;
        } else {
            return _faceRegular;
        }
    }

    void RenderFTFontManager::loadFontFaces()
    {
        int error = FT_Init_FreeType(&_library);
        if (error)
        {
            throw std::runtime_error("error loading freetype");
        }

        error = FT_New_Memory_Face(_library, sans_regular, sans_regular_size, 0, &_faceRegular);
        if (error)
        {
            throw std::runtime_error("error loading font regular");
        }

        error = FT_New_Memory_Face(_library, sans_bold, sans_bold_size, 0, &_faceBold);
        if (error)
        {
            throw std::runtime_error("error loading font bold");
        }

        error = FT_New_Memory_Face(_library, sans_italic, sans_italic_size, 0, &_faceItalic);
        if (error)
        {
            throw std::runtime_error("error loading font italic");
        }

        error = FT_New_Memory_Face(_library, sans_bold_italic, sans_bold_italic_size, 0, &_faceBoldItalic);
        if (error)
        {
            throw std::runtime_error("error loading font bold italic");
        }

        static const cairo_user_data_key_t key = {0};

        {
            _cairoFaceRegular = cairo_ft_font_face_create_for_ft_face (_faceRegular, 0);
            auto status = cairo_font_face_set_user_data (_cairoFaceRegular, &key,
                                    _faceRegular, (cairo_destroy_func_t) FT_Done_Face);
            if (status) {
                cairo_font_face_destroy (_cairoFaceRegular);
                FT_Done_Face (_faceRegular);
                throw std::runtime_error("error creating cairo font face regular");
            }
        }

        static const cairo_user_data_key_t key1 = {0};
        {
            _cairoFaceBold = cairo_ft_font_face_create_for_ft_face (_faceBold, 0);
            auto status = cairo_font_face_set_user_data (_cairoFaceBold, &key1,
                                    _faceBold, (cairo_destroy_func_t) FT_Done_Face);
            if (status) {
                cairo_font_face_destroy (_cairoFaceBold);
                FT_Done_Face (_faceBold);
                throw std::runtime_error("error creating cairo font face bold");
            }
        }

        static const cairo_user_data_key_t key2 = {0};
        {
            _cairoFaceItalic = cairo_ft_font_face_create_for_ft_face (_faceItalic, 0);
            auto status = cairo_font_face_set_user_data (_cairoFaceItalic, &key2,
                                    _faceItalic, (cairo_destroy_func_t) FT_Done_Face);
            if (status) {
                cairo_font_face_destroy (_cairoFaceItalic);
                FT_Done_Face (_faceItalic);
                throw std::runtime_error("error creating cairo font face italic");
            }
        }

        static const cairo_user_data_key_t key3 = {0};
        {
            _cairoFaceBoldItalic = cairo_ft_font_face_create_for_ft_face (_faceBoldItalic, 0);
            auto status = cairo_font_face_set_user_data (_cairoFaceBoldItalic, &key3,
                                    _faceBoldItalic, (cairo_destroy_func_t) FT_Done_Face);
            if (status) {
                cairo_font_face_destroy (_cairoFaceBoldItalic);
                FT_Done_Face (_faceBoldItalic);
                throw std::runtime_error("error creating cairo font face bold italic");
            }
        }
    }
}