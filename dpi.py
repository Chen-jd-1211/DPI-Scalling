import ctypes
from ctypes import wintypes
class NONCLIENTMETRICSW(ctypes.Structure):
    _fields_ = [
        ('cbSize', wintypes.UINT),
        ('iBorderWidth', wintypes.INT),
        ('iScrollWidth', wintypes.INT),
        ('iScrollHeight', wintypes.INT),
        ('iCaptionWidth', wintypes.INT),
        ('iCaptionHeight', wintypes.INT),
        ('lfCaptionFont', wintypes.LOGFONTW),
        ('iSmCaptionWidth', wintypes.INT),
        ('iSmCaptionHeight', wintypes.INT),
        ('lfSmCaptionFont', wintypes.LOGFONTW),
        ('iMenuWidth', wintypes.INT),
        ('iMenuHeight', wintypes.INT),
        ('lfMenuFont', wintypes.LOGFONTW),
        ('lfStatusFont', wintypes.LOGFONTW),
        ('lfMessageFont', wintypes.LOGFONTW),
        ('iPaddedBorderWidth', wintypes.INT)
    ]
SPI_SETNONCLIENTMETRICS = 0x0029
def set_dpi(new_dpi):
    user32 = ctypes.windll.user32
    ncm = NONCLIENTMETRICSW()
    ncm.cbSize = ctypes.sizeof(NONCLIENTMETRICSW)
    user32.SystemParametersInfoW(SPI_SETNONCLIENTMETRICS, ncm.cbSize, ctypes.byref(ncm), 0)
    ncm.lfCaptionFont.lfHeight = int(new_dpi * 96 / 72)
    ncm.lfSmCaptionFont.lfHeight = int(new_dpi * 96 / 72)
    ncm.lfMenuFont.lfHeight = int(new_dpi * 96 / 72)
    ncm.lfStatusFont.lfHeight = int(new_dpi * 96 / 72)
    ncm.lfMessageFont.lfHeight = int(new_dpi * 96 / 72)
    user32.SystemParametersInfoW(SPI_SETNONCLIENTMETRICS, ncm.cbSize, ctypes.byref(ncm), 0)
    return new_dpi