#include "EDF.hh"

namespace {
  using transitions = std::array<std::array<States, 128>, (size_t) States::NUMBER_STATES>;
  using acceptings = std::array<bool, (size_t) States::NUMBER_STATES>;

  constexpr transitions build_transitions() {
    transitions transitions_table = {};
    
    for (size_t i = 0; i < (size_t) States::NUMBER_STATES; i++) {
      for (size_t j = 0; j < 128; j++) {
        transitions_table[i][j] = States::UNKNOWN;
      }
    }

    for (size_t i = 0; i < 128; i++) {
      transitions_table[(size_t) States::CHAR_START][i] = States::CHAR_BODY;

      transitions_table[(size_t) States::STRING_START][i] = States::STRING_BODY;
      transitions_table[(size_t) States::STRING_BODY][i] = States::STRING_BODY;

      transitions_table[(size_t) States::TEMPLATE_START][(size_t) i] = States::TEMPLATE_BODY;
      transitions_table[(size_t) States::TEMPLATE_BODY][(size_t) i] = States::TEMPLATE_BODY;
    }

    for (size_t i = (size_t) 'A'; i <= (size_t) 'Z'; i++) {
      transitions_table[(size_t) States::START][(size_t) i] = States::IDENTIFIER;
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }
    
    for (size_t i = (size_t) 'a'; i <= (size_t) 'z'; i++) {
      transitions_table[(size_t) States::START][(size_t) i] = States::IDENTIFIER;
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }
    
    for (size_t i = (size_t) '0'; i <= (size_t) '9'; i++) {
      transitions_table[(size_t) States::START][i] = States::INTEGER_LITERAL;
      transitions_table[(size_t) States::INTEGER_LITERAL][i] = States::INTEGER_LITERAL;

      transitions_table[(size_t) States::FLOAT_LITERAL][i] = States::FLOAT_LITERAL;
      
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }

    transitions_table[(size_t) States::START][(size_t) '='] = States::EQUALS_PARTIAL;
    transitions_table[(size_t) States::START][(size_t) '&'] = States::AND_PARTIAL;

    transitions_table[(size_t) States::START][(size_t) '_'] = States::IDENTIFIER;
    transitions_table[(size_t) States::IDENTIFIER][(size_t) '_'] = States::IDENTIFIER;

    transitions_table[(size_t) States::INTEGER_LITERAL][(size_t) '.'] = States::FLOAT_LITERAL;

    transitions_table[(size_t) States::START][(size_t) '\''] = States::CHAR_START;
    transitions_table[(size_t) States::CHAR_BODY][(size_t) '\''] = States::CHAR_END;
    transitions_table[(size_t) States::CHAR_START][(size_t) '\''] = States::CHAR_END;

    transitions_table[(size_t) States::START][(size_t) '"'] = States::STRING_START;
    transitions_table[(size_t) States::STRING_BODY][(size_t) '"'] = States::STRING_END;
    transitions_table[(size_t) States::STRING_START][(size_t) '"'] = States::STRING_END;

    transitions_table[(size_t) States::START][(size_t) '`'] = States::TEMPLATE_START;
    transitions_table[(size_t) States::TEMPLATE_BODY][(size_t) '`'] = States::TEMPLATE_END;
    transitions_table[(size_t) States::TEMPLATE_START][(size_t) '`'] = States::TEMPLATE_END;

    transitions_table[(size_t) States::START][(size_t) '('] = States::LEFT_PARENTHESIS;
    transitions_table[(size_t) States::START][(size_t) ')'] = States::RIGHT_PARENTHESIS;
    transitions_table[(size_t) States::START][(size_t) '['] = States::LEFT_BRACKET;
    transitions_table[(size_t) States::START][(size_t) ']'] = States::RIGHT_BRACKET;
    transitions_table[(size_t) States::START][(size_t) '{'] = States::LEFT_BRACE;
    transitions_table[(size_t) States::START][(size_t) '}'] = States::RIGHT_BRACE;
    transitions_table[(size_t) States::START][(size_t) ','] = States::COMMA;
    transitions_table[(size_t) States::START][(size_t) '@'] = States::AT;
    transitions_table[(size_t) States::START][(size_t) '#'] = States::POUND;
    transitions_table[(size_t) States::START][(size_t) '$'] = States::DOLLAR;
    transitions_table[(size_t) States::START][(size_t) '?'] = States::QUESTION;

    transitions_table[(size_t) States::START][(size_t) ':'] = States::COLON;
    transitions_table[(size_t) States::START][(size_t) '|'] = States::TYPE_OR;

    transitions_table[(size_t) States::START][(size_t) '+'] = States::PLUS;
    transitions_table[(size_t) States::START][(size_t) '-'] = States::MINUS;
    transitions_table[(size_t) States::START][(size_t) '*'] = States::MULT;
    transitions_table[(size_t) States::START][(size_t) '/'] = States::DIV;
    transitions_table[(size_t) States::START][(size_t) '%'] = States::MOD;

    transitions_table[(size_t) States::AND_PARTIAL][(size_t) '&'] = States::AND;
    transitions_table[(size_t) States::TYPE_OR][(size_t) '|'] = States::OR;
    transitions_table[(size_t) States::START][(size_t) '!'] = States::NOT;

    transitions_table[(size_t) States::START][(size_t) '>'] = States::GREATER_THAN;
    transitions_table[(size_t) States::START][(size_t) '<'] = States::LESS_THAN;
    transitions_table[(size_t) States::GREATER_THAN][(size_t) '='] = States::GREATER_EQUALS;
    transitions_table[(size_t) States::LESS_THAN][(size_t) '='] = States::LESS_EQUALS;
    transitions_table[(size_t) States::EQUALS_PARTIAL][(size_t) '='] = States::EQUALS;
    transitions_table[(size_t) States::NOT][(size_t) '='] = States::NOT_EQUALS;

    return transitions_table;
  }

  constexpr acceptings build_acceptings() {
    acceptings acceptings_table = {};
    
    for (size_t i = 0; i < (size_t) States::NUMBER_STATES; i++) {
      acceptings_table[i] = false;
    }

    acceptings_table[(size_t) States::IDENTIFIER] = true;
    acceptings_table[(size_t) States::INTEGER_LITERAL] = true;
    acceptings_table[(size_t) States::FLOAT_LITERAL] = true;

    acceptings_table[(size_t) States::TEMPLATE_END] = true;
    acceptings_table[(size_t) States::STRING_END] = true;
    acceptings_table[(size_t) States::CHAR_END] = true;

    acceptings_table[(size_t) States::LEFT_PARENTHESIS] = true;
    acceptings_table[(size_t) States::RIGHT_PARENTHESIS] = true;
    acceptings_table[(size_t) States::LEFT_BRACKET] = true;
    acceptings_table[(size_t) States::RIGHT_BRACKET] = true;
    acceptings_table[(size_t) States::LEFT_BRACE] = true;
    acceptings_table[(size_t) States::RIGHT_BRACE] = true;
    acceptings_table[(size_t) States::COMMA] = true;
    acceptings_table[(size_t) States::AT] = true;
    acceptings_table[(size_t) States::POUND] = true;
    acceptings_table[(size_t) States::DOLLAR] = true;
    acceptings_table[(size_t) States::QUESTION] = true;

    acceptings_table[(size_t) States::COLON] = true;
    acceptings_table[(size_t) States::TYPE_OR] = true;

    acceptings_table[(size_t) States::PLUS] = true;
    acceptings_table[(size_t) States::MINUS] = true;
    acceptings_table[(size_t) States::MULT] = true;
    acceptings_table[(size_t) States::DIV] = true;
    acceptings_table[(size_t) States::MOD] = true;

    acceptings_table[(size_t) States::AND] = true;
    acceptings_table[(size_t) States::OR] = true;
    acceptings_table[(size_t) States::NOT] = true;

    acceptings_table[(size_t) States::GREATER_THAN] = true;
    acceptings_table[(size_t) States::LESS_THAN] = true;
    acceptings_table[(size_t) States::GREATER_EQUALS] = true;
    acceptings_table[(size_t) States::LESS_EQUALS] = true;
    acceptings_table[(size_t) States::EQUALS] = true;
    acceptings_table[(size_t) States::NOT_EQUALS] = true;

    return acceptings_table;
  }

  static constexpr transitions transition_table = build_transitions();
  static constexpr acceptings acceptings_table = build_acceptings();
}

std::vector<Token> EDF::Lexer::tokenize() {
  std::vector<Token> tokens = {};
  States last = States::START;
  size_t start_position;

  for (size_t i = 0; i < source.length(); i++) {
    if (last == States::START) {
      i = handle_unwanted(i);
      start_position = i;
      if (i >= source.length()) break;
    }

    char current = source[i];
    States next = transition_table[(size_t) last][(unsigned char) current];

    if (next != States::UNKNOWN) {
      last = next;
    } else {
      auto return_block = finalize_state(last, start_position, i);
      
      if (return_block.state == States::UNKNOWN) 
        throw new std::runtime_error("ERROR: Unknown Lexical Token at line " + std::to_string(line_number) + ".\n");
      else
        tokens.push_back(Token(return_block.state, return_block.lexeme, line_number));

      last = States::START;
      start_position = --i;
    }
  }

  // return if it finished cleanly
  if (last == States::START)
    return tokens;

  // final token flush
  auto return_block = finalize_state(last, start_position, source.length());
  if (return_block.state == States::UNKNOWN) 
    throw new std::runtime_error("ERROR: Unknown Lexical Token at line " + std::to_string(line_number) + ".\n");
  else
    tokens.push_back(Token(return_block.state, return_block.lexeme, line_number));

  return tokens;
}

size_t EDF::Lexer::handle_whitespace(size_t start_position) {
  size_t position = start_position;

  while (
    position < source.length()
    && (source[position] == ' ' || source[position] == '\n' || source[position] == '\t')
  ) {
    if (source[position] == '\n')
      line_number++;
    position++;
  }

  return position;
}

size_t EDF::Lexer::handle_single_line_comments(size_t start_position) {
  size_t position = start_position;

  while (position < source.length() && source[position] != '\n') {
    position++;
  }

  // clears \n
  if (position < source.length()) {
    position++;
    line_number++;
  }

  return position;
}

size_t EDF::Lexer::handle_multiline_comments(size_t start_position) {
  size_t position = start_position;

  while (position + 1 < source.length() && !(source[position] == '*' && source[position + 1] == '/')) {
    if (source[position] == '\n')
      line_number++;
    
    position++;
  }

  position += 2; // clears */

  return position;
}

size_t EDF::Lexer::handle_unwanted(size_t start_position) {
  size_t position = start_position;

  while (true) {
    position = handle_whitespace(position);

    if (position + 1 < source.length() && source[position] == '/' && source[position + 1] == '/')
      position = handle_single_line_comments(position);
    else if (position + 1 < source.length() && source[position] == '/' && source[position + 1] == '*')
      position = handle_multiline_comments(position);
    else break;
  }

  return position;
}

EDF::Lexer::Finalized_Return EDF::Lexer::finalize_state(States state, size_t start_position, size_t position) {
  std::string_view lexeme = source.substr(start_position, position - start_position);

  if (!acceptings_table[(size_t) state])
    return EDF::Lexer::Finalized_Return(States::UNKNOWN, lexeme);

  switch (state) {
    case States::CHAR_END:
      return EDF::Lexer::Finalized_Return(States::CHAR_LITERAL, lexeme.substr(1, lexeme.length() - 2));
    case States::STRING_END:
      return EDF::Lexer::Finalized_Return(States::STRING_LITERAL, lexeme.substr(1, lexeme.length() - 2));
    case States::TEMPLATE_END:
      return EDF::Lexer::Finalized_Return(States::TEMPLATE_LITERAL, lexeme.substr(1, lexeme.length() - 2));
    default:
      return EDF::Lexer::Finalized_Return(state, lexeme);
  }
}
