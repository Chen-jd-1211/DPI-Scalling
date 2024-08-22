import ctypes
import ctypes.wintypes
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
        ('iPaddedBorderWidth', wintypes.INT)]
class LOGFONTW(ctypes.Structure):
    _fields_ = [
        ('lfHeight', wintypes.LONG),
        ('lfWidth', wintypes.LONG),
        ('lfEscapement', wintypes.LONG),
        ('lfOrientation', wintypes.LONG),
        ('lfWeight', wintypes.LONG),
        ('lfItalic', wintypes.BYTE),
        ('lfUnderline', wintypes.BYTE),
        ('lfStrikeOut', wintypes.BYTE),
        ('lfCharSet', wintypes.BYTE),
        ('lfOutPrecision', wintypes.BYTE),
        ('lfClipPrecision', wintypes.BYTE),
        ('lfQuality', wintypes.BYTE),
        ('lfPitchAndFamily', wintypes.BYTE),
        ('lfFaceName', wintypes.WCHAR * 32)
    ]
SPI_SETNONCLIENTMETRICS = 0x0029
def set_dpi(new_dpi):
    user32 = ctypes.windll.user32
    ncm = NONCLIENTMETRICSW()
    ncm.cbSize = ctypes.sizeof(NONCLIENTMETRICSW)
    user32.SystemParametersInfoW(SPI_SETNONCLIENTMETRICS, ncm.cbSize, ctypes.byref(ncm), 0)
    ncm.lfCaptionFont[0] = int(new_dpi * 96 / 72)
    ncm.lfSmCaptionFont[0] = int(new_dpi * 96 / 72)
    ncm.lfMenuFont[0] = int(new_dpi * 96 / 72)
    ncm.lfStatusFont[0] = int(new_dpi * 96 / 72)
    ncm.lfMessageFont[0] = int(new_dpi * 96 / 72)
    user32.SystemParametersInfoW(SPI_SETNONCLIENTMETRICS, ncm.cbSize, ctypes.byref(ncm), 0)
    return new_dpi

# 示例：将DPI设置为150%
new_dpi = set_dpi(150)
print("New DPI:", new_dpi)