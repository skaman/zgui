#include "imgui.h"

#include "../imguifiledialog/ImGuiFileDialog.h"

#ifndef ZGUI_API
#define ZGUI_API
#endif

extern "C"
{
    struct ZGUI_API imguifiledialog_FileDialogConfig
    {
        const char *path;
        const char *fileName;
        const char *filePathName;
        int countSelectionMax;
        void *userDatas;
        ImGuiFileDialogFlags flags;
        float sidePaneWidth;
    };

    ZGUI_API void imguifiledialog_OpenDialog(const char *key, const char *title, const char *filters,
                                             imguifiledialog_FileDialogConfig const *fileDialogConfig)
    {
        IGFD::FileDialogConfig config = {};
        config.path = fileDialogConfig->path;
        config.fileName = fileDialogConfig->fileName;
        config.filePathName = fileDialogConfig->filePathName;
        config.countSelectionMax = fileDialogConfig->countSelectionMax;
        config.userDatas = fileDialogConfig->userDatas;
        config.flags = fileDialogConfig->flags;
        config.sidePaneWidth = fileDialogConfig->sidePaneWidth;
        ImGuiFileDialog::Instance()->OpenDialog(key, title, filters, config);
    }

    ZGUI_API bool imguifiledialog_Display(const char *key, ImGuiWindowFlags flags,
                                          float min_size_x, float min_size_y,
                                          float max_size_x, float max_size_y)
    {
        return ImGuiFileDialog::Instance()->Display(key, flags, {min_size_x, min_size_y}, {max_size_x, max_size_y});
    }

    ZGUI_API void imguifiledialog_Close()
    {
        ImGuiFileDialog::Instance()->Close();
    }

    ZGUI_API bool imguifiledialog_WasOpenedThisFrameByKey(const char *key)
    {
        return ImGuiFileDialog::Instance()->WasOpenedThisFrame(key);
    }

    ZGUI_API bool imguifiledialog_WasOpenedThisFrame()
    {
        return ImGuiFileDialog::Instance()->WasOpenedThisFrame();
    }

    ZGUI_API bool imguifiledialog_IsOpenedByKey(const char *key)
    {
        return ImGuiFileDialog::Instance()->IsOpened(key);
    }

    ZGUI_API bool imguifiledialog_IsOpened()
    {
        return ImGuiFileDialog::Instance()->IsOpened();
    }

    ZGUI_API void imguifiledialog_GetOpenedKey(char *buffer, size_t bufferSize)
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetOpenedKey();
        std::strncpy(buffer, filePath.c_str(), bufferSize);
        buffer[bufferSize - 1] = '\0';
    }

    ZGUI_API bool imguifiledialog_IsOk()
    {
        return ImGuiFileDialog::Instance()->IsOk();
    }

    ZGUI_API struct imguifiledialog_SelectionItem
    {
        const char *fileName;
        const char *filePathName;
    };

    ZGUI_API struct imguifiledialog_Selection
    {
        imguifiledialog_SelectionItem *items;
        size_t count;
    };

    ZGUI_API void imguifiledialog_FreeSelection(imguifiledialog_Selection *selection)
    {
        if (selection == nullptr)
            return;
        for (size_t i = 0; i < selection->count; ++i)
        {
            delete[] selection->items[i].fileName;
            delete[] selection->items[i].filePathName;
        }
        delete[] selection->items;
        selection->items = nullptr;
        selection->count = 0;
    }

    ZGUI_API imguifiledialog_Selection imguifiledialog_GetSelection(IGFD_ResultMode resultMode)
    {
        std::map<std::string, std::string> selection = ImGuiFileDialog::Instance()->GetSelection(resultMode);

        imguifiledialog_Selection result;
        result.count = selection.size();
        result.items = new imguifiledialog_SelectionItem[result.count];

        size_t index = 0;
        for (const auto &pair : selection)
        {
            // Copia chiavi e valori in modo dinamico
            result.items[index].fileName = new char[pair.first.size() + 1];
            std::strcpy((char *)result.items[index].fileName, pair.first.c_str());

            result.items[index].filePathName = new char[pair.second.size() + 1];
            std::strcpy((char *)result.items[index].filePathName, pair.second.c_str());

            ++index;
        }

        return result;
    }

    ZGUI_API void imguifiledialog_GetFilePathName(char *buffer, size_t bufferSize, IGFD_ResultMode resultMode)
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName(resultMode);
        std::strncpy(buffer, filePath.c_str(), bufferSize);
        buffer[bufferSize - 1] = '\0';
    }

    ZGUI_API void imguifiledialog_GetCurrentFileName(char *buffer, size_t bufferSize, IGFD_ResultMode resultMode)
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetCurrentFileName(resultMode);
        std::strncpy(buffer, filePath.c_str(), bufferSize);
        buffer[bufferSize - 1] = '\0';
    }

    ZGUI_API void imguifiledialog_GetCurrentPath(char *buffer, size_t bufferSize)
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
        std::strncpy(buffer, filePath.c_str(), bufferSize);
        buffer[bufferSize - 1] = '\0';
    }

    ZGUI_API void imguifiledialog_GetCurrentFilter(char *buffer, size_t bufferSize)
    {
        std::string filePath = ImGuiFileDialog::Instance()->GetCurrentFilter();
        std::strncpy(buffer, filePath.c_str(), bufferSize);
        buffer[bufferSize - 1] = '\0';
    }

    ZGUI_API void *imguifiledialog_GetUserDatas()
    {
        return ImGuiFileDialog::Instance()->GetUserDatas();
    }

    ZGUI_API struct imguifiledialog_FileStyle
    {
        ImU32 color;
        const char *icon;
        ImFont *font;
        IGFD_FileStyleFlags flags;
    };

    ZGUI_API void imguifiledialog_SetFileStyle(IGFD_FileStyleFlags flags, const char *criteria,
                                               imguifiledialog_FileStyle *infos)
    {
        IGFD::FileStyle style;
        style.color = ImGui::ColorConvertU32ToFloat4(infos->color);
        if (infos->icon != nullptr)
            style.icon = infos->icon;
        style.font = infos->font;
        style.flags = infos->flags;
        ImGuiFileDialog::Instance()->SetFileStyle(flags, criteria, style);
    }

    ZGUI_API bool imguifiledialog_GetFileStyle(IGFD_FileStyleFlags flags, const char *criteria,
                                               ImU32 *outColor, const char **outIcon, ImFont **outFont)
    {
        ImVec4 color;
        std::string icon;
        bool result = ImGuiFileDialog::Instance()->GetFileStyle(flags, criteria, &color, &icon, outFont);
        if (result)
        {
            *outColor = ImGui::ColorConvertFloat4ToU32(color);
            *outIcon = icon.c_str();
        }
        return result;
    }

    ZGUI_API void imguifiledialog_ClearFilesStyle()
    {
        ImGuiFileDialog::Instance()->ClearFilesStyle();
    }

    ZGUI_API void imguifiledialog_SetLocales(int localeCategory, const char *localeBegin, const char *localeEnd)
    {
        ImGuiFileDialog::Instance()->SetLocales(localeCategory, localeBegin, localeEnd);
    }
}
