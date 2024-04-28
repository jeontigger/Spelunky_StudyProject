#pragma once

namespace math {
	/// <summary>
	/// row �ִ밪�� col �ִ밪�� ���� value�� �ش� row, col�� ��ȯ���ִ� �Լ�
	/// </summary>
	/// <param name="value">��</param>
	/// <param name="mRow">�ִ� row</param>
	/// <param name="mCol">�ִ� col</param>
	/// <returns>��ȯ�� row col</returns>
	static Vec2 IdxToRowCol(int value, Vec2 RC) {
		return Vec2(value / (int)RC.x, value % (int)RC.y);
	}

	static int RowColToIdx(Vec2 value, Vec2 RC) {
		return int(value.y * RC.y + value.x);
	}
}