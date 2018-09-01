//
// Created by jannis on 30.08.18.
//

#ifndef NOVA_RENDERER_VULKAN_RENDER_ENGINE_HPP
#define NOVA_RENDERER_VULKAN_RENDER_ENGINE_HPP

#ifdef __linux__
#define VK_USE_PLATFORM_XLIB_KHR // Use X11 for window creating on Linux... TODO: Wayland?
#define NOVA_VK_XLIB
#endif
#include <vulkan/vulkan.h>
#include "../render_engine.hpp"
#include "vulkan_utils.hpp"
#include "x11_window.hpp"

namespace nova {
    class vulkan_render_engine : public render_engine {
    private:
        std::vector<const char *> enabled_validation_layer_names;

        VkInstance vk_instance;
#ifdef NOVA_VK_XLIB
        x11_window *window = nullptr;
#endif
        VkSurfaceKHR surface;
        VkDevice device;
        VkQueue graphics_queue;
        VkQueue present_queue;

        void create_device();

#ifndef NDEBUG
        PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
        PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
        PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;

        static VkBool32 debug_report_callback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT object_type, uint64_t object, size_t location, int32_t messageCode,
                const char *layer_prefix, const char *message, void *user_data);

        VkDebugReportCallbackEXT debug_callback;
#endif

    public:
        explicit vulkan_render_engine(const settings &settings);
        ~vulkan_render_engine();

        void open_window(uint32_t width, uint32_t height) override;

        command_buffer* allocate_command_buffer() override;

        void free_command_buffer(command_buffer* buf) override;

        static const std::string get_engine_name();
    };
}


#endif //NOVA_RENDERER_VULKAN_RENDER_ENGINE_HPP
