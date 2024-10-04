#!/bin/bash 

if ! which git >/dev/null; then
    echo "Git is not installed!"
    exit 1
fi

if [ -d /opt/numengine ]; then
    sudo rm -r /opt/numengine
fi

cd /tmp

git clone git@github.com:riley0122/numengine.git
rm -rf /tmp/numengine/.git
chmod +x /tmp/numengine/install_deps.sh

cd /tmp/numengine/src
python3 -m venv venv
source venv/bin/activate
venv/bin/python -m pip install -r /tmp/numengine/src/requirements.txt

sudo mv /tmp/numengine /opt/numengine
/opt/numengine/install_deps.sh

if which zsh >/dev/null; then
    if ! grep -q "alias numengine=" ~/.zshrc; then
        echo alias numengine=/opt/numengine/src/numengine.sh >> ~/.zshrc
    fi
fi

if ! grep -q "alias numengine=" ~/.bashrc; then
    echo alias numengine=/opt/numengine/src/numengine.sh >> ~/.bashrc
fi
