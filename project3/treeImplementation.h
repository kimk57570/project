

using namespace std;


template <typename T>
Tree<T>::Tree(const Tree& another) {
	if (another.isEmpty()) {
		return;
	}
	*this = another;

}

template <typename T>
Tree<T>::~Tree() {
	delete root;
}


template <typename T>
const Tree<T>& Tree<T>::operator=(const Tree& another) {
	if (this != &another) {
		delete root;
		root = new Node<T>(*another.root);
	}
	return *this;
}


template <typename T>
Tree<T>* Tree<T>::find(const T& data) {
	if (isEmpty()) {
		return nullptr;
	}
	if (root->data == data) {
		return this;
	}
	else if (root->data != data) {
		for (int i = 0; i < root->childCount; i++) {
			if (root->children[i].find(data) == nullptr) {
				continue;
			}
			else {
				return root->children[i].find(data);
			}
		}
	}
	return nullptr;
}


template <typename T>
const Tree<T>* Tree<T>::find(const T& data) const {
	if (isEmpty()) {
		return nullptr;
	}
	if (root->data == data) {
		return this;
	}
	else if (root->data != data) {
		for (int i = 0; i < root->childCount; i++) {
			if (root->children[i].find(data) == nullptr) {
				continue;
			}
			else {
				return root->children[i].find(data);
			}
		}
	}
	return nullptr;
}


template <typename T>
int Tree<T>::getDepth(const T& data) const {

	if(isEmpty()) {
		return -1;
	}
	if(find(data) == nullptr) {
		return -1;
	}
	if (root->data != data) {
		for (int i = 0; i < root->childCount; i++) {
			if (root->children[i].find(data) == nullptr) {
				continue;
			}
			else {
				return 1 + root->children[i].getDepth(data);
			}
		}
	}
	else if (root->data == data) {
		return 0;
	}
	return 0;
}


template <typename T>
int Tree<T>::getDescendantCount(const T& data) const {
	if(isEmpty()) {
		return -1;
	}
	if(find(data) == nullptr) {
		return -1;
	}
	return find(data)->getDescendantCount();
}


template <typename T>
int Tree<T>::getDescendantCount() const {
	if(isEmpty()) {
		return -1;
	}
	if(root->children == nullptr) {
		return 0;
	}
	else if (root->children != nullptr) {
		int x = 0;
		for (int i = 0; i < root->childCount; i++) {
			x = x + root->children[i].getDescendantCount();
		}
		return root->childCount + x;
	}
	return 0;
}


template <typename T>
bool Tree<T>::addRoot(const T& data) {
	if(find(data) != nullptr) {
		return false;
	}

	if(this->root != nullptr) {
		Tree<T>* x = new Tree<T>;
		x->root = this->root;
		this->root = new Node<T>(data,1);
		this->root->children[0] = *x;
		return true;

	}
	else if(this->root == nullptr) {
		this->root = new Node<T>(data);
		return true;
	}
	return false;

}


template <typename T>
bool Tree<T>::addChild(const T& parentData, const T& childData) {
	if(find(parentData) == nullptr) {
		return false;
	}
	if(find(childData) != nullptr) {
		return false;
	}

	Tree<T>* p = find(parentData);
	Tree<T>* c = new Tree<T>;
	c->root = new Node<T>(childData);

	Tree<T>* temp = new Tree<T>[p->root->childCount+1];
	for (int i = 0; i < p->root->childCount; i++) {
		temp[i] = p->root->children[i];
	}
	temp[p->root->childCount] = *c;
	delete [] p->root->children;
	p->root->children = temp;
	p->root->childCount += 1;
	return true;

}
