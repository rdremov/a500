// a500.cpp : Defines the entry point for the console application.
//
// https://techiedelight.quora.com/500-Data-Structures-and-Algorithms-interview-questions-and-their-solutions?share=1&utm_medium=email&utm_source=hackernewsletter&utm_term=code

#include <stdio.h>
#include <tchar.h>
#include <conio.h>

#include <vector>
#include <queue>
#include <algorithm>	// sort vector
#include <iostream>		// cout
using namespace std;

#include <windows.h>
class	Elapsed
{
public:
	Elapsed()
	{
		if( !s_freq.QuadPart )
			QueryPerformanceFrequency(&s_freq);
		Start();
	}
	~Elapsed()
	{
		double msec = Stop();
		printf("Elapsed %10.3f msec ", msec);
	}

	void	Start()
	{
		QueryPerformanceCounter(&m_li0);
		m_li = m_li0;
	}

	double	Stop()
	{
		QueryPerformanceCounter(&m_li);
		double msec = (m_li.QuadPart - m_li0.QuadPart) / (s_freq.QuadPart / 1000.);
		return msec;
	}

private:
	LARGE_INTEGER m_li0;
	LARGE_INTEGER m_li;
	static LARGE_INTEGER s_freq;
};

LARGE_INTEGER Elapsed::s_freq = {0};

// ARRAY:

// BACKTRACKING:
// Print all possible solutions to N Queens problem
class ProblemNqueen
{
public:
	ProblemNqueen(int N)
	{
		m_index = 0;
		m_N = N;
		m_board.resize(m_N * m_N);
	}

	~ProblemNqueen()
	{
		printf("For N=%d found %d solutions\n", m_N, m_index);
	}

	void	Solve(int row = 0)
	{
		if( row == m_N )
		{
			// SOLVED: N queens are on the board
			m_index++;
			Print();
			return;
		}

		int offset = row * m_N;
		for(int col=0; col<m_N; col++)
		{
			if( Test(row, col) )
			{
				m_board[offset + col] = true;	// place queen
				Solve(row + 1);
				m_board[offset + col] = false;	// restore
			}
		}
	}

protected:
	void	Print()
	{
		printf("solution %d:\n", m_index);
		for(int row=0; row<m_N; row++)
		{
			int offset = row * m_N;
			for(int col=0; col<m_N; col++)
				printf("%c", m_board[offset + col] ? 'Q' : '-');
			printf("\n");
		}
		printf("\n");
	}

	bool	Test(int row, int col)
	{
		for(int nn=0; nn<m_N; nn++)
		{
			if( m_board[row * m_N + nn] )
				return false;
			if( m_board[nn * m_N + col] )
				return false;
		}

		int dd = row;
		if( dd > col)
			dd = col;
		for(int ii=row-dd, jj=col-dd; ii<m_N && jj<m_N; ii++, jj++)
		{
			if( m_board[ii * m_N + jj] )
				return false;;
		}

		dd = m_N - 1 - col;
		if( dd > row )
			dd = row;
		for(int ii=row-dd, jj=col+dd; ii<m_N && jj>=0; ii++, jj--)
		{
			if( m_board[ii * m_N + jj] )
				return false;
		}
		
		return true;
	}

private:
	int				m_N;
	int				m_index;
	vector<bool>	m_board;
};

// Find the shortest path in maze
void	ProblemShortestPathInMaze()
{
	const int N = 4;
	const int M = 5;
	const bool maze[N][M] = {
		{0, 1, 1, 1, 0},
		{1, 1, 0, 1, 1},
		{0, 1, 0, 0, 1},
		{0, 1, 1, 1, 0}};

	struct Node
	{
		int	x;
		int	y;
		int	dist;

		Node(int xx=0, int yy=0, int dd=0)
		{
			x = xx;
			y = yy;
			dist = dd;
		}

		bool operator==(const Node& node) const
		{
			return x == node.x && y == node.y;
		}
	};

	const Node begin(1, 0);
	const Node end(2, 4);

	// walls are like visited nodes, so init with maze inversion
	bool visit[N][M];
	for(int i=0; i<N; i++)
		for(int j=0; j<M; j++)
			visit[i][j] = !maze[i][j];

	queue<Node> qu;	// similar to BFS

	// start with begin node
	qu.push(begin);
	visit[begin.x][begin.y] = true;

	while( !qu.empty() )
	{
		const Node& cur = qu.front();

		if( cur == end )
		{
			cout << "shortest path distance is " << cur.dist << endl;
			break;
		}

		// top
		if( cur.x > 0 && !visit[cur.x-1][cur.y] )
		{
			visit[cur.x-1][cur.y] = true;
			qu.push(Node(cur.x-1, cur.y, cur.dist+1));
		}

		// bottom
		if( cur.x+1 < N && !visit[cur.x+1][cur.y] )
		{
			visit[cur.x+1][cur.y] = true;
			qu.push(Node(cur.x+1, cur.y, cur.dist+1));
		}
		// left
		if( cur.y > 0 && !visit[cur.x][cur.y-1] )
		{
			visit[cur.x][cur.y-1] = true;
			qu.push(Node(cur.x, cur.y-1, cur.dist+1));
		}

		// right
		if( cur.y+1 < M && !visit[cur.x][cur.y+1] )
		{
			visit[cur.x][cur.y+1] = true;
			qu.push(Node(cur.x, cur.y+1, cur.dist+1));
		}

		qu.pop();
	}
}

// BINARY:

// BINARY TREES:

// BST:

// DIVIDE & CONQUER:

// DYNAMIC PROGRAMMING:

// GRAPHS:

// HEAP:

// LINKED LIST:

// MATRIX:

// QUEUE:

// SORTING:

// STACK:

// STRING:
void	ProblemStringRotatedPalindrome()
{
	string str = "CBAABCD";
	int i, n, len = str.length();

	// all rotations
	for(i=0; i<len; i++)
	{
		// test if polyndrome
		for(n=0; n<len/2; n++)
		{
			if( str[n] != str[len-1-n] )
				break;
		}
		if( n == len/2 )
		{
			cout << "Found palindrome" << '"' << str.c_str() << '"' << endl;
			return;
		}

		// rotate by one char
		char ch = str[0];
		str.erase(0, 1);
		str += ch;
	}
}

// TRIE:

// GREEDY:

// PUZZLES:


int _tmain(int argc, _TCHAR* argv[])
{
	//{ProblemNqueen pnq(8); pnq.Solve();}
	//ProblemShortestPathInMaze();
	ProblemStringRotatedPalindrome();

	printf("\npress any key to quit...\n");
	while( !_kbhit() );
	return 0;
}

