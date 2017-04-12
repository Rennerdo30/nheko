/*
 * nheko Copyright (C) 2017  Konstantinos Sideris <siderisk@auth.gr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>
#include <QMouseEvent>

#include "Ripple.h"
#include "RoomInfo.h"
#include "RoomInfoListItem.h"

RoomInfoListItem::RoomInfoListItem(RoomInfo info, QWidget *parent)
    : QWidget(parent)
    , info_(info)
    , is_pressed_(false)
    , max_height_(60)
{
	normal_style_ =
		"QWidget { color: #ebebeb; background-color: #232626; border-bottom: 1px solid #171919;}"
		"QLabel { border: none; }";

	pressed_style_ =
		"QWidget { background-color: #577275; color: #ebebeb;"
		"border-bottom: 1px solid #171919;}"
		"QLabel { border: none; }";

	setStyleSheet(normal_style_);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setAutoFillBackground(true);

	setMinimumSize(parent->width(), max_height_);

	topLayout_ = new QHBoxLayout(this);
	topLayout_->setSpacing(0);
	topLayout_->setMargin(0);

	avatarWidget_ = new QWidget(this);
	avatarWidget_->setMaximumSize(max_height_, max_height_);
	textWidget_ = new QWidget(this);

	avatarLayout_ = new QVBoxLayout(avatarWidget_);
	avatarLayout_->setSpacing(0);
	avatarLayout_->setContentsMargins(0, 5, 0, 5);

	textLayout_ = new QVBoxLayout(textWidget_);
	textLayout_->setSpacing(0);
	textLayout_->setContentsMargins(0, 5, 0, 5);

	roomAvatar_ = new Avatar(avatarWidget_);
	roomAvatar_->setLetter(QChar(info_.name()[0]));
	roomAvatar_->setSize(max_height_ - 20);
	avatarLayout_->addWidget(roomAvatar_);

	roomName_ = new QLabel(info_.name(), textWidget_);
	roomName_->setMaximumSize(parent->width() - 10, 20);
	roomName_->setStyleSheet("font-weight: 400; font-size: 14px;");
	roomName_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	roomTopic_ = new QLabel(info_.topic(), textWidget_);
	roomTopic_->setMaximumSize(parent->width() - 10, 20);
	roomTopic_->setStyleSheet("color: #c9c9c9; font-size: 12px");
	roomTopic_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	textLayout_->addWidget(roomName_);
	textLayout_->addWidget(roomTopic_);

	topLayout_->addWidget(avatarWidget_);
	topLayout_->addWidget(textWidget_);

	setElidedText(roomName_, info_.name(), parent->width() - 10);
	setElidedText(roomTopic_, info_.topic(), parent->width() - 10);

	QPainterPath path;
	path.addRoundedRect(rect(), 0, 0);

	ripple_overlay_ = new RippleOverlay(this);
	ripple_overlay_->setClipPath(path);
	ripple_overlay_->setClipping(true);

	setLayout(topLayout_);
}

void RoomInfoListItem::setPressedState(bool state)
{
	if (!is_pressed_ && state) {
		is_pressed_ = state;
		setStyleSheet(pressed_style_);
	} else if (is_pressed_ && !state) {
		is_pressed_ = state;
		setStyleSheet(normal_style_);
	}
}

void RoomInfoListItem::mousePressEvent(QMouseEvent *event)
{
	emit clicked(info_);

	setPressedState(true);

	// Ripple on mouse position by default.
	QPoint pos = event->pos();
	qreal radiusEndValue = static_cast<qreal>(width()) / 2;

	Ripple *ripple = new Ripple(pos);

	ripple->setRadiusEndValue(radiusEndValue);
	ripple->setOpacityStartValue(0.35);
	ripple->setColor(QColor("#171919"));
	ripple->radiusAnimation()->setDuration(300);
	ripple->opacityAnimation()->setDuration(500);

	ripple_overlay_->addRipple(ripple);
}

void RoomInfoListItem::setElidedText(QLabel *label, QString text, int width)
{
	QFontMetrics metrics(label->font());
	QString elidedText = metrics.elidedText(text, Qt::ElideRight, width);
	label->setText(elidedText);
}

RoomInfoListItem::~RoomInfoListItem()
{
}