#include "char_output.h"
#include "drivers/mock_char_output_driver.h"
#include "threads/mock_char_queue.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::tests;

class CharOutputTests : public testing::Test
{
public:
  CharOutputTests() :
    m_char_output(m_char_queue, m_char_output_driver)
  {
  }

protected:
  MockCharQueue m_char_queue{};
  MockCharOutputDriver m_char_output_driver{};
  CharOutput m_char_output;
};

TEST_F(CharOutputTests, run_task_gets_char_from_the_queue_and_sends_it_to_the_output_driver)
{
  // Given
  std::string text = "test\n";
  for (size_t i = 0; i < text.length(); i++)
  {
    m_char_queue.state.get_return_value.push_back(text[i]);
  }

  // When
  for (size_t i = 0; i < text.length(); i++)
  {
    m_char_output.RunThreadTask();
  }

  // Then
  ASSERT_EQ(text.length(), m_char_queue.state.get_call_count);
  ASSERT_EQ(text.length(), m_char_output_driver.state.output_call_count);
  ASSERT_TRUE(std::equal(text.begin(), text.end(), m_char_output_driver.state.output_text.begin()));
}

TEST_F(CharOutputTests, output_adds_chars_to_processing_queue)
{
  // Given
  std::string text = "Hello\n";

  // When
  m_char_output.Output(text.c_str());

  // Then
  ASSERT_EQ(text.length(), m_char_queue.state.add_call_count);
  ASSERT_TRUE(std::equal(text.begin(), text.end(), m_char_queue.state.add_letter.begin()));
}
