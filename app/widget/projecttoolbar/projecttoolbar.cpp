#include "projecttoolbar.h"

#include <QHBoxLayout>
#include <QEvent>
#include <QButtonGroup>

#include "ui/icons/icons.h"

ProjectToolbar::ProjectToolbar(QWidget *parent) :
  QWidget(parent)
{
  QHBoxLayout* layout = new QHBoxLayout(this);
  layout->setSpacing(0);
  layout->setMargin(0);

  new_button_ = new QPushButton();
  new_button_->setIcon(olive::icon::New);
  connect(new_button_, SIGNAL(clicked(bool)), this, SIGNAL(NewClicked()));
  layout->addWidget(new_button_);

  open_button_ = new QPushButton();
  open_button_->setIcon(olive::icon::Open);
  connect(open_button_, SIGNAL(clicked(bool)), this, SIGNAL(OpenClicked()));
  layout->addWidget(open_button_);

  save_button_ = new QPushButton();
  save_button_->setIcon(olive::icon::Save);
  connect(save_button_, SIGNAL(clicked(bool)), this, SIGNAL(SaveClicked()));
  layout->addWidget(save_button_);

  undo_button_ = new QPushButton();
  undo_button_->setIcon(olive::icon::Undo);
  connect(undo_button_, SIGNAL(clicked(bool)), this, SIGNAL(UndoClicked()));
  layout->addWidget(undo_button_);

  redo_button_ = new QPushButton();
  redo_button_->setIcon(olive::icon::Redo);
  connect(redo_button_, SIGNAL(clicked(bool)), this, SIGNAL(RedoClicked()));
  layout->addWidget(redo_button_);

  search_field_ = new QLineEdit();
  search_field_->setClearButtonEnabled(true);
  connect(search_field_, SIGNAL(textChanged(const QString &)), this, SIGNAL(SearchChanged(const QString&)));
  layout->addWidget(search_field_);

  tree_button_ = new QPushButton();
  tree_button_->setIcon(olive::icon::TreeView);
  tree_button_->setCheckable(true);
  connect(tree_button_, SIGNAL(clicked(bool)), this, SIGNAL(TreeViewClicked()));
  layout->addWidget(tree_button_);

  list_button_ = new QPushButton();
  list_button_->setIcon(olive::icon::ListView);
  list_button_->setCheckable(true);
  connect(list_button_, SIGNAL(clicked(bool)), this, SIGNAL(ListViewClicked()));
  layout->addWidget(list_button_);

  icon_button_ = new QPushButton();
  icon_button_->setIcon(olive::icon::IconView);
  icon_button_->setCheckable(true);
  connect(icon_button_, SIGNAL(clicked(bool)), this, SIGNAL(IconViewClicked()));
  layout->addWidget(icon_button_);

  // Group Tree/List/Icon view buttons into a button group for easy exclusive-buttons
  QButtonGroup* view_button_group = new QButtonGroup(this);
  view_button_group->setExclusive(true);
  view_button_group->addButton(tree_button_);
  view_button_group->addButton(list_button_);
  view_button_group->addButton(icon_button_);

  Retranslate();
}

void ProjectToolbar::changeEvent(QEvent *e)
{
  if (e->type() == QEvent::LanguageChange) {
    Retranslate();
  }
  QWidget::changeEvent(e);
}

void ProjectToolbar::Retranslate()
{
  new_button_->setToolTip(tr("New..."));
  open_button_->setToolTip(tr("Open Project"));
  save_button_->setToolTip(tr("Save Project"));
  undo_button_->setToolTip(tr("Undo"));
  redo_button_->setToolTip(tr("Redo"));

  search_field_->setPlaceholderText(tr("Search media, markers, etc."));

  tree_button_->setToolTip(tr("Switch to Tree View"));
  list_button_->setToolTip(tr("Switch to List View"));
  icon_button_->setToolTip(tr("Switch to Icon View"));
}