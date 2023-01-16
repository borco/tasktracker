.pragma library

function colorWithAlpha(color, alpha) {
    return Qt.hsla(color.hslHue, color.hslSaturation, color.hslLightness, alpha)
}

const DangerColor = "#ff0000"

const PopupX = 20
const PopupTop = 40
const PopupBottom = 20

const ErrorTextColor = "#ff0000"
const ErrorTextHeight = 11

const PageHeaderHeight = 42
const PageHeaderLeftMargin = 4
const PageHeaderRightMargin = 4

const ToolBarHeight = 32
const ToolBarSeparatorWidth = 2

const ToolButtonSize = 32
const ToolButtonPadding = 4
const ToolButtonCheckedRadius = 4

const ContentLeftMargin = 16
const ContentRightMargin = 16

const ConfigItemHeight = 28
const ConfigGroupTitleHeight = 48
const ConfigGroupTitleBottomMargin = 8
const ConfigGroupTitleFontWeight = 400

const DialogRadius = 12
const DialogPadding = 20
const DialogButtonsHeight = 40

const SplitViewSize = 1
const SplitViewHitAreaPadding = 4

const PopupContentBottomPadding = 12
const PopupItemTopMargin = 8
const PopupItemBottomMargin = 8
