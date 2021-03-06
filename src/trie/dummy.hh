#pragma once

#include "node.hh"

namespace trie
{
  /* Dummy command does not do anything and is used
   * only for tests purposes */
  class Dummy
  {
  public:
    Dummy(const std::vector<node>*){};

    Dummy(const Dummy&) = delete;
    const Dummy& operator=(const Dummy&) = delete;
    Dummy(Dummy&&) = delete;
    const Dummy& operator=(Dummy&&) = delete;

    using result_t = bool;
    result_t result_get() const
    {
      return true;
    }

    void operator()(index_t) {}
  };
} // namespace trie
