#include "ClipView.h"
#include "general.h"

Bool isClipViewCellVisible(IEEE64 clipViewCellLeft, IEEE64 clipViewCellRight, IEEE64 clipViewCellTop, IEEE64 clipViewCellBottom)
{
  return clipViewCellRight < boundLeft__ClipView__STATIC_FIELD || clipViewCellLeft > boundRight__ClipView__STATIC_FIELD || clipViewCellTop > boundBottom__ClipView__STATIC_FIELD || clipViewCellBottom < boundTop__ClipView__STATIC_FIELD ? false__Bool__STATIC_VALUE : true__Bool__STATIC_VALUE;
}
