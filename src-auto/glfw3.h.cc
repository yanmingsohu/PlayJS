//
// 2019-02-06 21:29:41
// create from D:\game\sanguo7\src-auto\generate-gl-code.js 
//
// D:\game\sanguo7\deps\glfw\include\GLFW\glfw3.h
#include "../src/gl.h"


GL_FUNC(glfwInit, args, ac) {
    GL_CHK_ARG(0, glfwInit());
    pushException("Unimplement function glfwInit(...)");
    return 0;
}


GL_FUNC(glfwTerminate, args, ac) {
    GL_CHK_ARG(0, glfwTerminate());
    pushException("Unimplement function glfwTerminate(...)");
    return 0;
}


GL_FUNC(glfwInitHint, args, ac) {
    GL_CHK_ARG(2, glfwInitHint(hint, value));
    pushException("Unimplement function glfwInitHint(...)");
    return 0;
}


// GL_FUNC(glfwGetVersion, args, ac) {
//     GL_CHK_ARG(3, glfwGetVersion(major, minor, rev));
//     pushException("Unimplement function glfwGetVersion(...)");
//     return 0;
// }


// GL_FUNC(glfwGetVersionString, args, ac) {
//     GL_CHK_ARG(0, glfwGetVersionString());
//     pushException("Unimplement function glfwGetVersionString(...)");
//     return 0;
// }


GL_FUNC(glfwGetError, args, ac) {
    GL_CHK_ARG(1, glfwGetError(description));
    pushException("Unimplement function glfwGetError(...)");
    return 0;
}


GL_FUNC(glfwSetErrorCallback, args, ac) {
    GL_CHK_ARG(1, glfwSetErrorCallback(cbfun));
    pushException("Unimplement function glfwSetErrorCallback(...)");
    return 0;
}


GL_FUNC(glfwGetMonitors, args, ac) {
    GL_CHK_ARG(1, glfwGetMonitors(count));
    pushException("Unimplement function glfwGetMonitors(...)");
    return 0;
}


// GL_FUNC(glfwGetPrimaryMonitor, args, ac) {
//     GL_CHK_ARG(0, glfwGetPrimaryMonitor());
//     pushException("Unimplement function glfwGetPrimaryMonitor(...)");
//     return 0;
// }


GL_FUNC(glfwGetMonitorPos, args, ac) {
    GL_CHK_ARG(3, glfwGetMonitorPos(monitor, xpos, ypos));
    pushException("Unimplement function glfwGetMonitorPos(...)");
    return 0;
}


GL_FUNC(glfwGetMonitorPhysicalSize, args, ac) {
    GL_CHK_ARG(3, glfwGetMonitorPhysicalSize(monitor, widthMM, heightMM));
    pushException("Unimplement function glfwGetMonitorPhysicalSize(...)");
    return 0;
}


GL_FUNC(glfwGetMonitorContentScale, args, ac) {
    GL_CHK_ARG(3, glfwGetMonitorContentScale(monitor, xscale, yscale));
    pushException("Unimplement function glfwGetMonitorContentScale(...)");
    return 0;
}


GL_FUNC(glfwGetMonitorName, args, ac) {
    GL_CHK_ARG(1, glfwGetMonitorName(monitor));
    pushException("Unimplement function glfwGetMonitorName(...)");
    return 0;
}


GL_FUNC(glfwSetMonitorUserPointer, args, ac) {
    GL_CHK_ARG(2, glfwSetMonitorUserPointer(monitor, pointer));
    pushException("Unimplement function glfwSetMonitorUserPointer(...)");
    return 0;
}


GL_FUNC(glfwGetMonitorUserPointer, args, ac) {
    GL_CHK_ARG(1, glfwGetMonitorUserPointer(monitor));
    pushException("Unimplement function glfwGetMonitorUserPointer(...)");
    return 0;
}


GL_FUNC(glfwSetMonitorCallback, args, ac) {
    GL_CHK_ARG(1, glfwSetMonitorCallback(cbfun));
    pushException("Unimplement function glfwSetMonitorCallback(...)");
    return 0;
}


GL_FUNC(glfwGetVideoModes, args, ac) {
    GL_CHK_ARG(2, glfwGetVideoModes(monitor, count));
    pushException("Unimplement function glfwGetVideoModes(...)");
    return 0;
}


// GL_FUNC(glfwGetVideoMode, args, ac) {
//     GL_CHK_ARG(1, glfwGetVideoMode(monitor));
//     pushException("Unimplement function glfwGetVideoMode(...)");
//     return 0;
// }


GL_FUNC(glfwSetGamma, args, ac) {
    GL_CHK_ARG(2, glfwSetGamma(monitor, gamma));
    pushException("Unimplement function glfwSetGamma(...)");
    return 0;
}


GL_FUNC(glfwGetGammaRamp, args, ac) {
    GL_CHK_ARG(1, glfwGetGammaRamp(monitor));
    pushException("Unimplement function glfwGetGammaRamp(...)");
    return 0;
}


GL_FUNC(glfwSetGammaRamp, args, ac) {
    GL_CHK_ARG(2, glfwSetGammaRamp(monitor, ramp));
    pushException("Unimplement function glfwSetGammaRamp(...)");
    return 0;
}


GL_FUNC(glfwDefaultWindowHints, args, ac) {
    GL_CHK_ARG(0, glfwDefaultWindowHints());
    pushException("Unimplement function glfwDefaultWindowHints(...)");
    return 0;
}


GL_FUNC(glfwWindowHint, args, ac) {
    GL_CHK_ARG(2, glfwWindowHint(hint, value));
    pushException("Unimplement function glfwWindowHint(...)");
    return 0;
}


GL_FUNC(glfwWindowHintString, args, ac) {
    GL_CHK_ARG(2, glfwWindowHintString(hint, value));
    pushException("Unimplement function glfwWindowHintString(...)");
    return 0;
}


// GL_FUNC(glfwCreateWindow, args, ac) {
//     GL_CHK_ARG(5, glfwCreateWindow(width, height, title, monitor, share));
//     pushException("Unimplement function glfwCreateWindow(...)");
//     return 0;
// }


// GL_FUNC(glfwDestroyWindow, args, ac) {
//     GL_CHK_ARG(1, glfwDestroyWindow(window));
//     pushException("Unimplement function glfwDestroyWindow(...)");
//     return 0;
// }


// GL_FUNC(glfwWindowShouldClose, args, ac) {
//     GL_CHK_ARG(1, glfwWindowShouldClose(window));
//     pushException("Unimplement function glfwWindowShouldClose(...)");
//     return 0;
// }


GL_FUNC(glfwSetWindowShouldClose, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowShouldClose(window, value));
    pushException("Unimplement function glfwSetWindowShouldClose(...)");
    return 0;
}


// GL_FUNC(glfwSetWindowTitle, args, ac) {
//     GL_CHK_ARG(2, glfwSetWindowTitle(window, title));
//     pushException("Unimplement function glfwSetWindowTitle(...)");
//     return 0;
// }


GL_FUNC(glfwSetWindowIcon, args, ac) {
    GL_CHK_ARG(3, glfwSetWindowIcon(window, count, images));
    pushException("Unimplement function glfwSetWindowIcon(...)");
    return 0;
}


GL_FUNC(glfwGetWindowPos, args, ac) {
    GL_CHK_ARG(3, glfwGetWindowPos(window, xpos, ypos));
    pushException("Unimplement function glfwGetWindowPos(...)");
    return 0;
}


// GL_FUNC(glfwSetWindowPos, args, ac) {
//     GL_CHK_ARG(3, glfwSetWindowPos(window, xpos, ypos));
//     pushException("Unimplement function glfwSetWindowPos(...)");
//     return 0;
// }


// GL_FUNC(glfwGetWindowSize, args, ac) {
//     GL_CHK_ARG(3, glfwGetWindowSize(window, width, height));
//     pushException("Unimplement function glfwGetWindowSize(...)");
//     return 0;
// }


GL_FUNC(glfwSetWindowSizeLimits, args, ac) {
    GL_CHK_ARG(5, glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight));
    pushException("Unimplement function glfwSetWindowSizeLimits(...)");
    return 0;
}


// GL_FUNC(glfwSetWindowAspectRatio, args, ac) {
//     GL_CHK_ARG(3, glfwSetWindowAspectRatio(window, numer, denom));
//     pushException("Unimplement function glfwSetWindowAspectRatio(...)");
//     return 0;
// }


// GL_FUNC(glfwSetWindowSize, args, ac) {
//     GL_CHK_ARG(3, glfwSetWindowSize(window, width, height));
//     pushException("Unimplement function glfwSetWindowSize(...)");
//     return 0;
// }


// GL_FUNC(glfwGetFramebufferSize, args, ac) {
//     GL_CHK_ARG(3, glfwGetFramebufferSize(window, width, height));
//     pushException("Unimplement function glfwGetFramebufferSize(...)");
//     return 0;
// }


GL_FUNC(glfwGetWindowFrameSize, args, ac) {
    GL_CHK_ARG(5, glfwGetWindowFrameSize(window, left, top, right, bottom));
    pushException("Unimplement function glfwGetWindowFrameSize(...)");
    return 0;
}


GL_FUNC(glfwGetWindowContentScale, args, ac) {
    GL_CHK_ARG(3, glfwGetWindowContentScale(window, xscale, yscale));
    pushException("Unimplement function glfwGetWindowContentScale(...)");
    return 0;
}


GL_FUNC(glfwGetWindowOpacity, args, ac) {
    GL_CHK_ARG(1, glfwGetWindowOpacity(window));
    pushException("Unimplement function glfwGetWindowOpacity(...)");
    return 0;
}


GL_FUNC(glfwSetWindowOpacity, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowOpacity(window, opacity));
    pushException("Unimplement function glfwSetWindowOpacity(...)");
    return 0;
}


GL_FUNC(glfwIconifyWindow, args, ac) {
    GL_CHK_ARG(1, glfwIconifyWindow(window));
    pushException("Unimplement function glfwIconifyWindow(...)");
    return 0;
}


GL_FUNC(glfwRestoreWindow, args, ac) {
    GL_CHK_ARG(1, glfwRestoreWindow(window));
    pushException("Unimplement function glfwRestoreWindow(...)");
    return 0;
}


GL_FUNC(glfwMaximizeWindow, args, ac) {
    GL_CHK_ARG(1, glfwMaximizeWindow(window));
    pushException("Unimplement function glfwMaximizeWindow(...)");
    return 0;
}


GL_FUNC(glfwShowWindow, args, ac) {
    GL_CHK_ARG(1, glfwShowWindow(window));
    pushException("Unimplement function glfwShowWindow(...)");
    return 0;
}


GL_FUNC(glfwHideWindow, args, ac) {
    GL_CHK_ARG(1, glfwHideWindow(window));
    pushException("Unimplement function glfwHideWindow(...)");
    return 0;
}


GL_FUNC(glfwFocusWindow, args, ac) {
    GL_CHK_ARG(1, glfwFocusWindow(window));
    pushException("Unimplement function glfwFocusWindow(...)");
    return 0;
}


GL_FUNC(glfwRequestWindowAttention, args, ac) {
    GL_CHK_ARG(1, glfwRequestWindowAttention(window));
    pushException("Unimplement function glfwRequestWindowAttention(...)");
    return 0;
}


// GL_FUNC(glfwGetWindowMonitor, args, ac) {
//     GL_CHK_ARG(1, glfwGetWindowMonitor(window));
//     pushException("Unimplement function glfwGetWindowMonitor(...)");
//     return 0;
// }


// GL_FUNC(glfwSetWindowMonitor, args, ac) {
//     GL_CHK_ARG(7, glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate));
//     pushException("Unimplement function glfwSetWindowMonitor(...)");
//     return 0;
// }


GL_FUNC(glfwGetWindowAttrib, args, ac) {
    GL_CHK_ARG(2, glfwGetWindowAttrib(window, attrib));
    pushException("Unimplement function glfwGetWindowAttrib(...)");
    return 0;
}


GL_FUNC(glfwSetWindowAttrib, args, ac) {
    GL_CHK_ARG(3, glfwSetWindowAttrib(window, attrib, value));
    pushException("Unimplement function glfwSetWindowAttrib(...)");
    return 0;
}


GL_FUNC(glfwSetWindowUserPointer, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowUserPointer(window, pointer));
    pushException("Unimplement function glfwSetWindowUserPointer(...)");
    return 0;
}


GL_FUNC(glfwGetWindowUserPointer, args, ac) {
    GL_CHK_ARG(1, glfwGetWindowUserPointer(window));
    pushException("Unimplement function glfwGetWindowUserPointer(...)");
    return 0;
}


GL_FUNC(glfwSetWindowPosCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowPosCallback(window, cbfun));
    pushException("Unimplement function glfwSetWindowPosCallback(...)");
    return 0;
}


GL_FUNC(glfwSetWindowSizeCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowSizeCallback(window, cbfun));
    pushException("Unimplement function glfwSetWindowSizeCallback(...)");
    return 0;
}


GL_FUNC(glfwSetWindowCloseCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowCloseCallback(window, cbfun));
    pushException("Unimplement function glfwSetWindowCloseCallback(...)");
    return 0;
}


GL_FUNC(glfwSetWindowRefreshCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowRefreshCallback(window, cbfun));
    pushException("Unimplement function glfwSetWindowRefreshCallback(...)");
    return 0;
}


GL_FUNC(glfwSetWindowFocusCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowFocusCallback(window, cbfun));
    pushException("Unimplement function glfwSetWindowFocusCallback(...)");
    return 0;
}


GL_FUNC(glfwSetWindowIconifyCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowIconifyCallback(window, cbfun));
    pushException("Unimplement function glfwSetWindowIconifyCallback(...)");
    return 0;
}


GL_FUNC(glfwSetWindowMaximizeCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowMaximizeCallback(window, cbfun));
    pushException("Unimplement function glfwSetWindowMaximizeCallback(...)");
    return 0;
}


GL_FUNC(glfwSetFramebufferSizeCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetFramebufferSizeCallback(window, cbfun));
    pushException("Unimplement function glfwSetFramebufferSizeCallback(...)");
    return 0;
}


GL_FUNC(glfwSetWindowContentScaleCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetWindowContentScaleCallback(window, cbfun));
    pushException("Unimplement function glfwSetWindowContentScaleCallback(...)");
    return 0;
}


// GL_FUNC(glfwPollEvents, args, ac) {
//     GL_CHK_ARG(0, glfwPollEvents());
//     pushException("Unimplement function glfwPollEvents(...)");
//     return 0;
// }


// GL_FUNC(glfwWaitEvents, args, ac) {
//     GL_CHK_ARG(0, glfwWaitEvents());
//     pushException("Unimplement function glfwWaitEvents(...)");
//     return 0;
// }


// GL_FUNC(glfwWaitEventsTimeout, args, ac) {
//     GL_CHK_ARG(1, glfwWaitEventsTimeout(timeout));
//     pushException("Unimplement function glfwWaitEventsTimeout(...)");
//     return 0;
// }


GL_FUNC(glfwPostEmptyEvent, args, ac) {
    GL_CHK_ARG(0, glfwPostEmptyEvent());
    pushException("Unimplement function glfwPostEmptyEvent(...)");
    return 0;
}


GL_FUNC(glfwGetInputMode, args, ac) {
    GL_CHK_ARG(2, glfwGetInputMode(window, mode));
    pushException("Unimplement function glfwGetInputMode(...)");
    return 0;
}


GL_FUNC(glfwSetInputMode, args, ac) {
    GL_CHK_ARG(3, glfwSetInputMode(window, mode, value));
    pushException("Unimplement function glfwSetInputMode(...)");
    return 0;
}


GL_FUNC(glfwGetKeyName, args, ac) {
    GL_CHK_ARG(2, glfwGetKeyName(key, scancode));
    pushException("Unimplement function glfwGetKeyName(...)");
    return 0;
}


GL_FUNC(glfwGetKeyScancode, args, ac) {
    GL_CHK_ARG(1, glfwGetKeyScancode(key));
    pushException("Unimplement function glfwGetKeyScancode(...)");
    return 0;
}


GL_FUNC(glfwGetKey, args, ac) {
    GL_CHK_ARG(2, glfwGetKey(window, key));
    pushException("Unimplement function glfwGetKey(...)");
    return 0;
}


GL_FUNC(glfwGetMouseButton, args, ac) {
    GL_CHK_ARG(2, glfwGetMouseButton(window, button));
    pushException("Unimplement function glfwGetMouseButton(...)");
    return 0;
}


GL_FUNC(glfwGetCursorPos, args, ac) {
    GL_CHK_ARG(3, glfwGetCursorPos(window, xpos, ypos));
    pushException("Unimplement function glfwGetCursorPos(...)");
    return 0;
}


GL_FUNC(glfwSetCursorPos, args, ac) {
    GL_CHK_ARG(3, glfwSetCursorPos(window, xpos, ypos));
    pushException("Unimplement function glfwSetCursorPos(...)");
    return 0;
}


GL_FUNC(glfwCreateCursor, args, ac) {
    GL_CHK_ARG(3, glfwCreateCursor(image, xhot, yhot));
    pushException("Unimplement function glfwCreateCursor(...)");
    return 0;
}


GL_FUNC(glfwCreateStandardCursor, args, ac) {
    GL_CHK_ARG(1, glfwCreateStandardCursor(shape));
    pushException("Unimplement function glfwCreateStandardCursor(...)");
    return 0;
}


GL_FUNC(glfwDestroyCursor, args, ac) {
    GL_CHK_ARG(1, glfwDestroyCursor(cursor));
    pushException("Unimplement function glfwDestroyCursor(...)");
    return 0;
}


GL_FUNC(glfwSetCursor, args, ac) {
    GL_CHK_ARG(2, glfwSetCursor(window, cursor));
    pushException("Unimplement function glfwSetCursor(...)");
    return 0;
}


GL_FUNC(glfwSetKeyCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetKeyCallback(window, cbfun));
    pushException("Unimplement function glfwSetKeyCallback(...)");
    return 0;
}


GL_FUNC(glfwSetCharCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetCharCallback(window, cbfun));
    pushException("Unimplement function glfwSetCharCallback(...)");
    return 0;
}


GL_FUNC(glfwSetCharModsCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetCharModsCallback(window, cbfun));
    pushException("Unimplement function glfwSetCharModsCallback(...)");
    return 0;
}


GL_FUNC(glfwSetMouseButtonCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetMouseButtonCallback(window, cbfun));
    pushException("Unimplement function glfwSetMouseButtonCallback(...)");
    return 0;
}


GL_FUNC(glfwSetCursorPosCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetCursorPosCallback(window, cbfun));
    pushException("Unimplement function glfwSetCursorPosCallback(...)");
    return 0;
}


GL_FUNC(glfwSetCursorEnterCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetCursorEnterCallback(window, cbfun));
    pushException("Unimplement function glfwSetCursorEnterCallback(...)");
    return 0;
}


GL_FUNC(glfwSetScrollCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetScrollCallback(window, cbfun));
    pushException("Unimplement function glfwSetScrollCallback(...)");
    return 0;
}


GL_FUNC(glfwSetDropCallback, args, ac) {
    GL_CHK_ARG(2, glfwSetDropCallback(window, cbfun));
    pushException("Unimplement function glfwSetDropCallback(...)");
    return 0;
}


GL_FUNC(glfwJoystickPresent, args, ac) {
    GL_CHK_ARG(1, glfwJoystickPresent(jid));
    pushException("Unimplement function glfwJoystickPresent(...)");
    return 0;
}


GL_FUNC(glfwGetJoystickAxes, args, ac) {
    GL_CHK_ARG(2, glfwGetJoystickAxes(jid, count));
    pushException("Unimplement function glfwGetJoystickAxes(...)");
    return 0;
}


GL_FUNC(glfwGetJoystickButtons, args, ac) {
    GL_CHK_ARG(2, glfwGetJoystickButtons(jid, count));
    pushException("Unimplement function glfwGetJoystickButtons(...)");
    return 0;
}


GL_FUNC(glfwGetJoystickHats, args, ac) {
    GL_CHK_ARG(2, glfwGetJoystickHats(jid, count));
    pushException("Unimplement function glfwGetJoystickHats(...)");
    return 0;
}


GL_FUNC(glfwGetJoystickName, args, ac) {
    GL_CHK_ARG(1, glfwGetJoystickName(jid));
    pushException("Unimplement function glfwGetJoystickName(...)");
    return 0;
}


GL_FUNC(glfwGetJoystickGUID, args, ac) {
    GL_CHK_ARG(1, glfwGetJoystickGUID(jid));
    pushException("Unimplement function glfwGetJoystickGUID(...)");
    return 0;
}


GL_FUNC(glfwSetJoystickUserPointer, args, ac) {
    GL_CHK_ARG(2, glfwSetJoystickUserPointer(jid, pointer));
    pushException("Unimplement function glfwSetJoystickUserPointer(...)");
    return 0;
}


GL_FUNC(glfwGetJoystickUserPointer, args, ac) {
    GL_CHK_ARG(1, glfwGetJoystickUserPointer(jid));
    pushException("Unimplement function glfwGetJoystickUserPointer(...)");
    return 0;
}


GL_FUNC(glfwJoystickIsGamepad, args, ac) {
    GL_CHK_ARG(1, glfwJoystickIsGamepad(jid));
    pushException("Unimplement function glfwJoystickIsGamepad(...)");
    return 0;
}


GL_FUNC(glfwSetJoystickCallback, args, ac) {
    GL_CHK_ARG(1, glfwSetJoystickCallback(cbfun));
    pushException("Unimplement function glfwSetJoystickCallback(...)");
    return 0;
}


GL_FUNC(glfwUpdateGamepadMappings, args, ac) {
    GL_CHK_ARG(1, glfwUpdateGamepadMappings(string));
    pushException("Unimplement function glfwUpdateGamepadMappings(...)");
    return 0;
}


GL_FUNC(glfwGetGamepadName, args, ac) {
    GL_CHK_ARG(1, glfwGetGamepadName(jid));
    pushException("Unimplement function glfwGetGamepadName(...)");
    return 0;
}


GL_FUNC(glfwGetGamepadState, args, ac) {
    GL_CHK_ARG(2, glfwGetGamepadState(jid, state));
    pushException("Unimplement function glfwGetGamepadState(...)");
    return 0;
}


GL_FUNC(glfwSetClipboardString, args, ac) {
    GL_CHK_ARG(2, glfwSetClipboardString(window, string));
    pushException("Unimplement function glfwSetClipboardString(...)");
    return 0;
}


GL_FUNC(glfwGetClipboardString, args, ac) {
    GL_CHK_ARG(1, glfwGetClipboardString(window));
    pushException("Unimplement function glfwGetClipboardString(...)");
    return 0;
}


// GL_FUNC(glfwGetTime, args, ac) {
//     GL_CHK_ARG(0, glfwGetTime());
//     pushException("Unimplement function glfwGetTime(...)");
//     return 0;
// }


GL_FUNC(glfwSetTime, args, ac) {
    GL_CHK_ARG(1, glfwSetTime(time));
    pushException("Unimplement function glfwSetTime(...)");
    return 0;
}


GL_FUNC(glfwGetTimerValue, args, ac) {
    GL_CHK_ARG(0, glfwGetTimerValue());
    pushException("Unimplement function glfwGetTimerValue(...)");
    return 0;
}


GL_FUNC(glfwGetTimerFrequency, args, ac) {
    GL_CHK_ARG(0, glfwGetTimerFrequency());
    pushException("Unimplement function glfwGetTimerFrequency(...)");
    return 0;
}


// GL_FUNC(glfwMakeContextCurrent, args, ac) {
//     GL_CHK_ARG(1, glfwMakeContextCurrent(window));
//     pushException("Unimplement function glfwMakeContextCurrent(...)");
//     return 0;
// }


GL_FUNC(glfwGetCurrentContext, args, ac) {
    GL_CHK_ARG(0, glfwGetCurrentContext());
    pushException("Unimplement function glfwGetCurrentContext(...)");
    return 0;
}


// GL_FUNC(glfwSwapBuffers, args, ac) {
//     GL_CHK_ARG(1, glfwSwapBuffers(window));
//     pushException("Unimplement function glfwSwapBuffers(...)");
//     return 0;
// }


// GL_FUNC(glfwSwapInterval, args, ac) {
//     GL_CHK_ARG(1, glfwSwapInterval(interval));
//     pushException("Unimplement function glfwSwapInterval(...)");
//     return 0;
// }


GL_FUNC(glfwExtensionSupported, args, ac) {
    GL_CHK_ARG(1, glfwExtensionSupported(extension));
    pushException("Unimplement function glfwExtensionSupported(...)");
    return 0;
}


GL_FUNC(glfwGetProcAddress, args, ac) {
    GL_CHK_ARG(1, glfwGetProcAddress(procname));
    pushException("Unimplement function glfwGetProcAddress(...)");
    return 0;
}


GL_FUNC(glfwVulkanSupported, args, ac) {
    GL_CHK_ARG(0, glfwVulkanSupported());
    pushException("Unimplement function glfwVulkanSupported(...)");
    return 0;
}


GL_FUNC(glfwGetRequiredInstanceExtensions, args, ac) {
    GL_CHK_ARG(1, glfwGetRequiredInstanceExtensions(count));
    pushException("Unimplement function glfwGetRequiredInstanceExtensions(...)");
    return 0;
}


GL_FUNC(glfwGetInstanceProcAddress, args, ac) {
    GL_CHK_ARG(2, glfwGetInstanceProcAddress(instance, procname));
    pushException("Unimplement function glfwGetInstanceProcAddress(...)");
    return 0;
}


GL_FUNC(glfwGetPhysicalDevicePresentationSupport, args, ac) {
    GL_CHK_ARG(3, glfwGetPhysicalDevicePresentationSupport(instance, device, queuefamily));
    pushException("Unimplement function glfwGetPhysicalDevicePresentationSupport(...)");
    return 0;
}


GL_FUNC(glfwCreateWindowSurface, args, ac) {
    GL_CHK_ARG(4, glfwCreateWindowSurface(instance, window, allocator, surface));
    pushException("Unimplement function glfwCreateWindowSurface(...)");
    return 0;
}


void auto_bind_glfw3_h(VM*vm, LocalVal& gl) {
    GL_BIND(glfwInit);
    GL_BIND(glfwTerminate);
    GL_BIND(glfwInitHint);
    // GL_BIND(glfwGetVersion);
    // GL_BIND(glfwGetVersionString);
    GL_BIND(glfwGetError);
    GL_BIND(glfwSetErrorCallback);
    GL_BIND(glfwGetMonitors);
    // GL_BIND(glfwGetPrimaryMonitor);
    GL_BIND(glfwGetMonitorPos);
    GL_BIND(glfwGetMonitorPhysicalSize);
    GL_BIND(glfwGetMonitorContentScale);
    GL_BIND(glfwGetMonitorName);
    GL_BIND(glfwSetMonitorUserPointer);
    GL_BIND(glfwGetMonitorUserPointer);
    GL_BIND(glfwSetMonitorCallback);
    GL_BIND(glfwGetVideoModes);
    // GL_BIND(glfwGetVideoMode);
    GL_BIND(glfwSetGamma);
    GL_BIND(glfwGetGammaRamp);
    GL_BIND(glfwSetGammaRamp);
    GL_BIND(glfwDefaultWindowHints);
    GL_BIND(glfwWindowHint);
    GL_BIND(glfwWindowHintString);
    // GL_BIND(glfwCreateWindow);
    // GL_BIND(glfwDestroyWindow);
    // GL_BIND(glfwWindowShouldClose);
    GL_BIND(glfwSetWindowShouldClose);
    // GL_BIND(glfwSetWindowTitle);
    GL_BIND(glfwSetWindowIcon);
    GL_BIND(glfwGetWindowPos);
    // GL_BIND(glfwSetWindowPos);
    // GL_BIND(glfwGetWindowSize);
    GL_BIND(glfwSetWindowSizeLimits);
    // GL_BIND(glfwSetWindowAspectRatio);
    // GL_BIND(glfwSetWindowSize);
    // GL_BIND(glfwGetFramebufferSize);
    GL_BIND(glfwGetWindowFrameSize);
    GL_BIND(glfwGetWindowContentScale);
    GL_BIND(glfwGetWindowOpacity);
    GL_BIND(glfwSetWindowOpacity);
    GL_BIND(glfwIconifyWindow);
    GL_BIND(glfwRestoreWindow);
    GL_BIND(glfwMaximizeWindow);
    GL_BIND(glfwShowWindow);
    GL_BIND(glfwHideWindow);
    GL_BIND(glfwFocusWindow);
    GL_BIND(glfwRequestWindowAttention);
    // GL_BIND(glfwGetWindowMonitor);
    // GL_BIND(glfwSetWindowMonitor);
    GL_BIND(glfwGetWindowAttrib);
    GL_BIND(glfwSetWindowAttrib);
    GL_BIND(glfwSetWindowUserPointer);
    GL_BIND(glfwGetWindowUserPointer);
    GL_BIND(glfwSetWindowPosCallback);
    GL_BIND(glfwSetWindowSizeCallback);
    GL_BIND(glfwSetWindowCloseCallback);
    GL_BIND(glfwSetWindowRefreshCallback);
    GL_BIND(glfwSetWindowFocusCallback);
    GL_BIND(glfwSetWindowIconifyCallback);
    GL_BIND(glfwSetWindowMaximizeCallback);
    GL_BIND(glfwSetFramebufferSizeCallback);
    GL_BIND(glfwSetWindowContentScaleCallback);
    // GL_BIND(glfwPollEvents);
    // GL_BIND(glfwWaitEvents);
    // GL_BIND(glfwWaitEventsTimeout);
    GL_BIND(glfwPostEmptyEvent);
    GL_BIND(glfwGetInputMode);
    GL_BIND(glfwSetInputMode);
    GL_BIND(glfwGetKeyName);
    GL_BIND(glfwGetKeyScancode);
    GL_BIND(glfwGetKey);
    GL_BIND(glfwGetMouseButton);
    GL_BIND(glfwGetCursorPos);
    GL_BIND(glfwSetCursorPos);
    GL_BIND(glfwCreateCursor);
    GL_BIND(glfwCreateStandardCursor);
    GL_BIND(glfwDestroyCursor);
    GL_BIND(glfwSetCursor);
    GL_BIND(glfwSetKeyCallback);
    GL_BIND(glfwSetCharCallback);
    GL_BIND(glfwSetCharModsCallback);
    GL_BIND(glfwSetMouseButtonCallback);
    GL_BIND(glfwSetCursorPosCallback);
    GL_BIND(glfwSetCursorEnterCallback);
    GL_BIND(glfwSetScrollCallback);
    GL_BIND(glfwSetDropCallback);
    GL_BIND(glfwJoystickPresent);
    GL_BIND(glfwGetJoystickAxes);
    GL_BIND(glfwGetJoystickButtons);
    GL_BIND(glfwGetJoystickHats);
    GL_BIND(glfwGetJoystickName);
    GL_BIND(glfwGetJoystickGUID);
    GL_BIND(glfwSetJoystickUserPointer);
    GL_BIND(glfwGetJoystickUserPointer);
    GL_BIND(glfwJoystickIsGamepad);
    GL_BIND(glfwSetJoystickCallback);
    GL_BIND(glfwUpdateGamepadMappings);
    GL_BIND(glfwGetGamepadName);
    GL_BIND(glfwGetGamepadState);
    GL_BIND(glfwSetClipboardString);
    GL_BIND(glfwGetClipboardString);
    // GL_BIND(glfwGetTime);
    GL_BIND(glfwSetTime);
    GL_BIND(glfwGetTimerValue);
    GL_BIND(glfwGetTimerFrequency);
    // GL_BIND(glfwMakeContextCurrent);
    GL_BIND(glfwGetCurrentContext);
    // GL_BIND(glfwSwapBuffers);
    // GL_BIND(glfwSwapInterval);
    GL_BIND(glfwExtensionSupported);
    GL_BIND(glfwGetProcAddress);
    GL_BIND(glfwVulkanSupported);
    GL_BIND(glfwGetRequiredInstanceExtensions);
    GL_BIND(glfwGetInstanceProcAddress);
    GL_BIND(glfwGetPhysicalDevicePresentationSupport);
    GL_BIND(glfwCreateWindowSurface);
}
