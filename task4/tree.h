#pragma once

#include <memory>

namespace bintree {
    template<typename Type>
    struct TNode : public std::enable_shared_from_this<TNode<Type>> {
        using TNodePtr = std::shared_ptr<TNode<Type>>;
        using TNodeWeakPtr = std::weak_ptr<TNode<Type>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<Type>>;
        using TNodeConstWeakPtr = std::weak_ptr<const TNode<Type>>;


        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        bool hasParent() const {
            return bool(parent);
        }

        Type &getValue() {
            return value;
        }

        const Type &getValue() const {
            return value;
        }

        TNodePtr getLeft() {
            return left;
        }

        TNodeConstPtr getLeft() const {
            return left;
        }

        TNodePtr getRight() {
            return right;
        }

        TNodeConstPtr getRight() const {
            return right;
        }

        TNodePtr getParent() {
            return (!parent.expired() ? parent.lock() : nullptr);
        }

        TNodeConstPtr getParent() const {
            return (!parent.expired() ? parent.lock() : nullptr);
        }

        static TNodePtr createLeaf(Type value) {
            return std::make_shared<TNode>(TNode(value));
        }

        static TNodePtr fork(Type v, TNodePtr left, TNodePtr right) {
            TNodePtr root = std::make_shared<TNode>(TNode(v, left, right));
            setParent(root->getLeft(), root);
            setParent(root->getRight(), root);
            return root;
        }

        TNodePtr replaceLeft(TNodePtr new_left) {
            setParent(new_left, this->shared_from_this());
            setParent(left, TNodeWeakPtr());
            std::swap(new_left, left);
            return new_left;
        }

        TNodePtr replaceRight(TNodePtr new_right) {
            setParent(new_right, this->shared_from_this());
            setParent(right, TNodeWeakPtr());
            std::swap(new_right, right);
            return new_right;
        }

        TNodePtr replaceRightWithLeaf(Type v) {
            return replaceRight(createLeaf(v));
        }

        TNodePtr replaceLeftWithLeaf(Type v) {
            return replaceLeft(createLeaf(v));
        }

        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }

        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }

    private:
        Type value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        TNodeWeakPtr parent = TNodeWeakPtr();

        TNode(Type value) : value(value) {}

        TNode(Type value, TNodePtr left, TNodePtr right)
                : value(value), left(left), right(right) {
        }

        static void setParent(TNodePtr node, TNodeWeakPtr parent) {
            if (node) {
                node->parent = parent;
            }
        }
    };
}
