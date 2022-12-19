#ifndef __render_ft_font_manger_h__
#define __render_ft_font_manager_h__
#include <cairo-ft.h>
#include <freetype/freetype.h>

namespace indigo
{
    class RenderFTFontManager
    {
    private:
        FT_Library  _library;
        FT_Face     _faceRegular;
        FT_Face     _faceItalic;
        FT_Face     _faceBold;
        FT_Face     _faceBoldItalic;

        cairo_font_face_t* _cairoFaceRegular = nullptr;
        cairo_font_face_t* _cairoFaceBold = nullptr;
        cairo_font_face_t* _cairoFaceItalic = nullptr;
        cairo_font_face_t* _cairoFaceBoldItalic = nullptr;

        void loadFontFaces();
    public:
        RenderFTFontManager();
        ~RenderFTFontManager();

        FT_Face selectFontFace(bool isBold, bool isItalic);
        cairo_font_face_t* selectCairoFontFace(bool isBold, bool isItalic);
    };
}

#endif