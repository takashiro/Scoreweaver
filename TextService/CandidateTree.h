
#ifndef CANDIDATETREE_H
#define CANDIDATETREE_H

#include <stdarg.h>

class CCandidateTree{
public:
	class Node{
	public:
		Node(Node *parent, wchar_t value);
		~Node();

		wchar_t GetValue() const;

		void AddChild(wchar_t key, wchar_t value);
		Node *GetChild(int key);
		Node *GetChild(wchar_t key);
		void RemoveChild(wchar_t key);

		void SetChildren(wstring keys, ...);
		//void SetChildren(const wstring &keys, const wstring &values);
		wstring GetChildren();
		void GetChildren(wstring &keys, wstring &values);
		void ClearChildren();

		bool IsEnd() const;
		bool HasChildren() const;

	private:
		Node *_parent;
		wchar_t _value;

		wstring _childrenKeys, _childrenValues;
		vector<Node *> _childrenNodes;
	};

	CCandidateTree();
	~CCandidateTree();

	CCandidateTree::Node *GetCurrent();

	bool ForwardTo(wchar_t child_key);
	void ToRoot();

private:
	Node *_root, *_current;
};

extern CCandidateTree *CandidateTree;

#endif